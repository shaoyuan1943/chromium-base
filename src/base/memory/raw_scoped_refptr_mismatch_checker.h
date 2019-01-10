// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_MEMORY_RAW_SCOPED_REFPTR_MISMATCH_CHECKER_H_
#define BASE_MEMORY_RAW_SCOPED_REFPTR_MISMATCH_CHECKER_H_

#include "base/memory/ref_counted.h"
#include "build/build_config.h"

#include <tuple>

// It is dangerous to post a task with a T* argument where T is a subtype of
// RefCounted(Base|ThreadSafeBase), since by the time the parameter is used, the
// object may already have been deleted since it was not held with a
// scoped_refptr. Example: http://crbug.com/27191
// The following set of traits are designed to generate a compile error
// whenever this antipattern is attempted.

namespace base {

// This is a base internal implementation file used by task.h and callback.h.
// Not for public consumption, so we wrap it in namespace internal.
namespace internal {

template <typename ...Types>
struct NeedsScopedRefptrButGetsRawPtr;

template <typename T>
struct NeedsScopedRefptrButGetsRawPtr<T> {
#if defined(OS_WIN)
  enum {
    value = std::false_type::value
  };
#else
  enum {
    // Human readable translation: you needed to be a scoped_refptr if you are a
    // raw pointer type and are convertible to a RefCounted(Base|ThreadSafeBase)
    // type.
    value = (std::is_pointer<T>::value && (std::is_convertible<T, subtle::RefCountedBase*>::value ||
      std::is_convertible<T, subtle::RefCountedThreadSafeBase*>::value))
  };
#endif
};

template <typename T, typename ...Types>
struct NeedsScopedRefptrButGetsRawPtr<T, Types...> {
  enum {
    value = NeedsScopedRefptrButGetsRawPtr<T>::value || NeedsScopedRefptrButGetsRawPtr<Types...>::value
  };
};

// ParamsUseScopedRefptrCorrectly的变参版本
template <typename ...Types>
struct ParamsUseScopedRefptrCorrectly;

template <typename T>
struct ParamsUseScopedRefptrCorrectly<T> {
  enum { value = 0 };
};

template <>
struct ParamsUseScopedRefptrCorrectly<std::tuple<>>{
  enum { value = 1 };
};

template <typename T>
struct ParamsUseScopedRefptrCorrectly<std::tuple<T>> {
  enum { value = !(NeedsScopedRefptrButGetsRawPtr<T>::value) };
};

template <typename ...Types>
struct ParamsUseScopedRefptrCorrectly<std::tuple<Types...>> {
  enum {
    value = !(NeedsScopedRefptrButGetsRawPtr<Types...>::value)
  };
};

}  // namespace internal

}  // namespace base

#endif  // BASE_MEMORY_RAW_SCOPED_REFPTR_MISMATCH_CHECKER_H_
