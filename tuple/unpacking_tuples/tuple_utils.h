#ifndef _TUPLE_UTILS_INCLUDED_ 
#define _TUPLE_UTILS_INCLUDED_

#include <utility>
#include <tuple>

namespace tu // tuple utility
{

/**
   idea http://aherrmann.github.io/programming/2016/02/28/unpacking-tuples-in-cpp14/ 
*/

template <typename F, size_t... Is>
constexpr 
decltype(auto) 
index_apply_impl(F&& f, std::index_sequence<Is...>) 
{
    return std::forward<F>(f)(std::integral_constant<size_t, Is> {}...);
}

template <size_t N, typename F>
   // where F is Callable (http://en.cppreference.com/w/cpp/concept/Callable) 
   // with a sequence of integral constants as variadic input. Signatute Ret (int<0>, int<1>, int<2>, ...)
constexpr 
decltype(auto) 
index_apply(F&& f) 
{
    return index_apply_impl(std::forward<F>(f), std::make_index_sequence<N>{});
}

/**
   \brief takes an ar­bi­trary tuple and re­turns a new tuple that holds the first N el­e­ments of the orig­inal tu­ple
*/
template <size_t N, typename Tuple>
constexpr 
decltype(auto) take_front(Tuple&& t) 
{
    return index_apply<N>([&](auto... Is) {
        return std::make_tuple(std::get<Is>(std::forward<Tuple>(t))...);
    });
}

/**
   \brief takes an ar­bi­trary tuple and re­turns a new tuple that holds the last N el­e­ments of the orig­inal tu­ple in reversed ordering
*/
template <size_t N, typename Tuple>
constexpr 
decltype(auto) take_back(Tuple&& t) 
{
    return index_apply<N>([&](auto... Is) {
         return std::make_tuple(std::get<std::tuple_size<std::decay_t<Tuple>>::value-1-Is>(std::forward<Tuple>(t))...);
    });
}

/**
   \brief takes a tuple and re­turns a new tuple that con­tains the orig­inal tu­ple’s el­e­ments in re­versed or­der.
*/
template <typename Tuple>
constexpr 
decltype(auto) 
reverse(Tuple&& t) 
{
   return take_back<std::tuple_size<std::decay_t<Tuple>>::value>(std::forward<Tuple>(t));
}

/**
   \brief takes a callable and a tuple and calls the callable with the el­e­ments of the tuple as ar­gu­ments.

   http://en.cppreference.com/w/cpp/utility/apply
*/
template <typename F, typename Tuple>
constexpr 
decltype(auto)
apply(F&& f, Tuple&& t)
{
   return index_apply<std::tuple_size<std::decay_t<Tuple>>::value>([&](auto... Is) {
      return std::forward<F>(f)(std::get<Is>(std::forward<Tuple>(t))...);
   });
}

/**
   \brief   takes a callable and a tuple and calls the callable with the each el­e­ment in a row in ordering elements of the tuple.
   \retval  a callable
   https://stackoverflow.com/questions/1198260/iterate-over-tuple
*/

template < size_t I = 0, typename F, typename... Tp>
constexpr 
typename std::enable_if<I<sizeof...(Tp),std::decay_t<F>>::type 
for_each(F&& f, std::tuple<Tp...>&& t)
{
   std::forward<F>(f)(std::get<I>(std::forward<std::tuple<Tp...>>(t)));
   return for_each<I+1>(std::forward<F>(f),std::forward<std::tuple<Tp...>>(t));
}

template < size_t I = 0, typename F, typename... Tp>
constexpr 
typename std::enable_if<I==sizeof...(Tp),std::decay_t<F>>::type 
for_each(F&& f, std::tuple<Tp...> t)
{
   return f;
}


} // end of tu

#endif // _TUPLE_UTILS_INCLUDED_