// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/threading/worker_pool.h"

#include "base/bind.h"
#include "base/callback.h"
#include "base/logging.h"
#include "base/pending_task.h"
#include "base/threading/thread_local.h"
#include "base/lazy_instance.h"

namespace base {

namespace {

base::LazyInstance<ThreadLocalBoolean>::Leaky
    g_worker_pool_running_on_this_thread = LAZY_INSTANCE_INITIALIZER;

DWORD CALLBACK WorkItemCallback(void* param) {
  PendingTask* pending_task = static_cast<PendingTask*>(param);

  g_worker_pool_running_on_this_thread.Get().Set(true);
  pending_task->task.Run();
  g_worker_pool_running_on_this_thread.Get().Set(false);
  delete pending_task;
  return 0;
}

// Takes ownership of |pending_task|
bool PostTaskInternal(PendingTask* pending_task, bool task_is_slow) {
  ULONG flags = 0;
  if (task_is_slow)
    flags |= WT_EXECUTELONGFUNCTION;

  if (!QueueUserWorkItem(WorkItemCallback, pending_task, flags)) {
    DLOG(ERROR) << "QueueUserWorkItem failed: " << GetLastError();
    delete pending_task;
    return false;
  }

  return true;
}

}  // namespace

// static
bool WorkerPool::PostTask(const tracked_objects::Location& from_here,
                          const base::Closure& task, bool task_is_slow) {
  PendingTask* pending_task = new PendingTask(from_here, task);
  return PostTaskInternal(pending_task, task_is_slow);
}

// static
bool WorkerPool::RunsTasksOnCurrentThread() {
  return g_worker_pool_running_on_this_thread.Get().Get();
}

}  // namespace base
