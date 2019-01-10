#ifndef BASE_DISPATCHERS_H__
#define BASE_DISPATCHERS_H__

#include <tuple>

// DON NOT USE *Impl FUNCTION!!!

// Dispatchers ----------------------------------------------------------------
//
// Helper functions that call the given method on an object, with the unpacked
// tuple arguments.  Notice that they all have the same number of arguments,
// so you need only write:
//   DispatchToMethod(object, &Object::method, args);
// This is very useful for templated dispatchers, since they don't need to know
// what type |args| is.

// Non-Static Dispatchers with no out params.
template <typename ObjectT, typename Method, size_t ...Index, typename ...ParamTypes>
inline void DispatchToMethodImpl(ObjectT* obj, Method method, const std::index_sequence<Index...>&,
  const std::tuple<ParamTypes...>& args) {

  (obj->*method)(std::get<Index>(args)...);
}

template <typename ObjectT, typename Method, typename ...ParamTypes>
inline void DispatchToMethod(ObjectT* obj, Method method, const std::tuple<ParamTypes...>& args) {
  DispatchToMethodImpl(obj, method, std::make_index_sequence<sizeof...(ParamTypes)>{}, args);
}

// Static Dispatchers with no out params.
template <typename Function, size_t ...Index, typename ...ParamTypes>
inline void DispatchToFunctionImpl(Function fn, const std::index_sequence<Index...>&,
  const std::tuple<ParamTypes...>& args) {

  (*fn)(std::get<Index>(args)...);
}

template <typename Function, typename ...ParamTypes>
inline void DispatchToFunction(Function fn, const std::tuple<ParamTypes...>& args) {
  DispatchToFunctionImpl(fn, std::make_index_sequence<sizeof...(ParamTypes)>{}, args);
}

#endif // BASE_DISPATCHERS_H__
