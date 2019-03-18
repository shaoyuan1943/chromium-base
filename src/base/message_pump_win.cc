// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/message_pump_win.h"

#include <math.h>

#include "base/message_loop.h"
#include "base/process_util.h"

namespace {

enum MessageLoopProblems {
  MESSAGE_POST_ERROR,
  COMPLETION_POST_ERROR,
  SET_TIMER_ERROR,
  MESSAGE_LOOP_PROBLEM_MAX,
};

}  // namespace

namespace base {

static const wchar_t kWndClass[] = L"Chrome_MessagePumpWindow";

// Message sent to get an additional time slice for pumping (processing) another
// task (a series of such messages creates a continuous task pump).
static const int kMsgHaveWork = WM_USER + 1;

//-----------------------------------------------------------------------------
// MessagePumpWin public:

void MessagePumpWin::AddObserver(MessagePumpObserver* observer) {
  observers_.AddObserver(observer);
}

void MessagePumpWin::RemoveObserver(MessagePumpObserver* observer) {
  observers_.RemoveObserver(observer);
}

void MessagePumpWin::WillProcessMessage(const MSG& msg) {
  FOR_EACH_OBSERVER(MessagePumpObserver, observers_, WillProcessEvent(msg));
}

void MessagePumpWin::DidProcessMessage(const MSG& msg) {
  FOR_EACH_OBSERVER(MessagePumpObserver, observers_, DidProcessEvent(msg));
}

void MessagePumpWin::RunWithDispatcher(
    Delegate* delegate, MessagePumpDispatcher* dispatcher) {
  RunState s;
  s.delegate = delegate;
  s.dispatcher = dispatcher;
  s.should_quit = false;
  s.run_depth = state_ ? state_->run_depth + 1 : 1;

  RunState* previous_state = state_;
  state_ = &s;

  DoRunLoop();

  state_ = previous_state;
}

void MessagePumpWin::Quit() {
  DCHECK(state_);
  state_->should_quit = true;
}

//-----------------------------------------------------------------------------
// MessagePumpWin protected:

int MessagePumpWin::GetCurrentDelay() const {
  if (delayed_work_time_.is_null())
    return -1;

  // Be careful here.  TimeDelta has a precision of microseconds, but we want a
  // value in milliseconds.  If there are 5.5ms left, should the delay be 5 or
  // 6?  It should be 6 to avoid executing delayed work too early.
  double timeout =
      ceil((delayed_work_time_ - TimeTicks::Now()).InMillisecondsF());

  // If this value is negative, then we need to run delayed work soon.
  int delay = static_cast<int>(timeout);
  if (delay < 0)
    delay = 0;

  return delay;
}

//-----------------------------------------------------------------------------
// MessagePumpForIO public:

MessagePumpForIO::MessagePumpForIO() {
  port_.Set(CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, 1));
  DCHECK(port_.IsValid());
}

void MessagePumpForIO::ScheduleWork() {
  if (InterlockedExchange(&have_work_, 1))
    return;  // Someone else continued the pumping.

  // Make sure the MessagePump does some work for us.
  BOOL ret = PostQueuedCompletionStatus(port_, 0,
    reinterpret_cast<ULONG_PTR>(this),
    reinterpret_cast<OVERLAPPED*>(this));
  if (ret)
    return;  // Post worked perfectly.

  // See comment in MessagePumpForUI::ScheduleWork() for this error recovery.
  InterlockedExchange(&have_work_, 0);  // Clarify that we didn't succeed.
}

void MessagePumpForIO::ScheduleDelayedWork(const TimeTicks& delayed_work_time) {
  // We know that we can't be blocked right now since this method can only be
  // called on the same thread as Run, so we only need to update our record of
  // how long to sleep when we do sleep.
  delayed_work_time_ = delayed_work_time;
}

void MessagePumpForIO::RegisterIOHandler(HANDLE file_handle,
  IOHandler* handler) {
  ULONG_PTR key = HandlerToKey(handler, true);
  HANDLE port = CreateIoCompletionPort(file_handle, port_, key, 1);
  DPCHECK(port);
}

bool MessagePumpForIO::RegisterJobObject(HANDLE job_handle,
  IOHandler* handler) {
  // Job object notifications use the OVERLAPPED pointer to carry the message
  // data. Mark the completion key correspondingly, so we will not try to
  // convert OVERLAPPED* to IOContext*.
  ULONG_PTR key = HandlerToKey(handler, false);
  JOBOBJECT_ASSOCIATE_COMPLETION_PORT info;
  info.CompletionKey = reinterpret_cast<void*>(key);
  info.CompletionPort = port_;
  return SetInformationJobObject(job_handle,
    JobObjectAssociateCompletionPortInformation,
    &info,
    sizeof(info)) != FALSE;
}

//-----------------------------------------------------------------------------
// MessagePumpForIO private:

void MessagePumpForIO::DoRunLoop() {
  for (;;) {
    // If we do any work, we may create more messages etc., and more work may
    // possibly be waiting in another task group.  When we (for example)
    // WaitForIOCompletion(), there is a good chance there are still more
    // messages waiting.  On the other hand, when any of these methods return
    // having done no work, then it is pretty unlikely that calling them
    // again quickly will find any work to do.  Finally, if they all say they
    // had no work, then it is a good time to consider sleeping (waiting) for
    // more work.

    bool more_work_is_plausible = state_->delegate->DoWork();
    if (state_->should_quit)
      break;

    more_work_is_plausible |= WaitForIOCompletion(0, NULL);
    if (state_->should_quit)
      break;

    more_work_is_plausible |=
        state_->delegate->DoDelayedWork(&delayed_work_time_);
    if (state_->should_quit)
      break;

    if (more_work_is_plausible)
      continue;

    more_work_is_plausible = state_->delegate->DoIdleWork();
    if (state_->should_quit)
      break;

    if (more_work_is_plausible)
      continue;

    WaitForWork();  // Wait (sleep) until we have work to do again.
  }
}

// Wait until IO completes, up to the time needed by the timer manager to fire
// the next set of timers.
void MessagePumpForIO::WaitForWork() {
  // We do not support nested IO message loops. This is to avoid messy
  // recursion problems.
  DCHECK_EQ(1, state_->run_depth) << "Cannot nest an IO message loop!";

  int timeout = GetCurrentDelay();
  if (timeout < 0)  // Negative value means no timers waiting.
    timeout = INFINITE;

  WaitForIOCompletion(timeout, NULL);
}

bool MessagePumpForIO::WaitForIOCompletion(DWORD timeout, IOHandler* filter) {
  IOItem item;
  if (completed_io_.empty() || !MatchCompletedIOItem(filter, &item)) {
    // We have to ask the system for another IO completion.
    if (!GetIOItem(timeout, &item))
      return false;

    if (ProcessInternalIOItem(item))
      return true;
  }

  // If |item.has_valid_io_context| is false then |item.context| does not point
  // to a context structure, and so should not be dereferenced, although it may
  // still hold valid non-pointer data.
  if (!item.has_valid_io_context || item.context->handler) {
    if (filter && item.handler != filter) {
      // Save this item for later
      completed_io_.push_back(item);
    } else {
      DCHECK(!item.has_valid_io_context ||
             (item.context->handler == item.handler));
      WillProcessIOEvent();
      item.handler->OnIOCompleted(item.context, item.bytes_transfered,
                                  item.error);
      DidProcessIOEvent();
    }
  } else {
    // The handler must be gone by now, just cleanup the mess.
    delete item.context;
  }
  return true;
}

// Asks the OS for another IO completion result.
bool MessagePumpForIO::GetIOItem(DWORD timeout, IOItem* item) {
  memset(item, 0, sizeof(*item));
  ULONG_PTR key = NULL;
  OVERLAPPED* overlapped = NULL;
  if (!GetQueuedCompletionStatus(port_.Get(), &item->bytes_transfered, &key,
                                 &overlapped, timeout)) {
    if (!overlapped)
      return false;  // Nothing in the queue.
    item->error = GetLastError();
    item->bytes_transfered = 0;
  }

  item->handler = KeyToHandler(key, &item->has_valid_io_context);
  item->context = reinterpret_cast<IOContext*>(overlapped);
  return true;
}

bool MessagePumpForIO::ProcessInternalIOItem(const IOItem& item) {
  if (this == reinterpret_cast<MessagePumpForIO*>(item.context) &&
      this == reinterpret_cast<MessagePumpForIO*>(item.handler)) {
    // This is our internal completion.
    DCHECK(!item.bytes_transfered);
    InterlockedExchange(&have_work_, 0);
    return true;
  }
  return false;
}

// Returns a completion item that was previously received.
bool MessagePumpForIO::MatchCompletedIOItem(IOHandler* filter, IOItem* item) {
  DCHECK(!completed_io_.empty());
  for (std::list<IOItem>::iterator it = completed_io_.begin();
       it != completed_io_.end(); ++it) {
    if (!filter || it->handler == filter) {
      *item = *it;
      completed_io_.erase(it);
      return true;
    }
  }
  return false;
}

void MessagePumpForIO::AddIOObserver(IOObserver *obs) {
  io_observers_.AddObserver(obs);
}

void MessagePumpForIO::RemoveIOObserver(IOObserver *obs) {
  io_observers_.RemoveObserver(obs);
}

void MessagePumpForIO::WillProcessIOEvent() {
  FOR_EACH_OBSERVER(IOObserver, io_observers_, WillProcessIOEvent());
}

void MessagePumpForIO::DidProcessIOEvent() {
  FOR_EACH_OBSERVER(IOObserver, io_observers_, DidProcessIOEvent());
}

// static
ULONG_PTR MessagePumpForIO::HandlerToKey(IOHandler* handler,
                                         bool has_valid_io_context) {
  ULONG_PTR key = reinterpret_cast<ULONG_PTR>(handler);

  // |IOHandler| is at least pointer-size aligned, so the lowest two bits are
  // always cleared. We use the lowest bit to distinguish completion keys with
  // and without the associated |IOContext|.
  DCHECK((key & 1) == 0);

  // Mark the completion key as context-less.
  if (!has_valid_io_context)
    key = key | 1;
  return key;
}

// static
MessagePumpForIO::IOHandler* MessagePumpForIO::KeyToHandler(
    ULONG_PTR key,
    bool* has_valid_io_context) {
  *has_valid_io_context = ((key & 1) == 0);
  return reinterpret_cast<IOHandler*>(key & ~static_cast<ULONG_PTR>(1));
}

}  // namespace base
