#include <numeric>
#include <iterator>
#include <type_traits>

/**
  \see https://github.com/nikolaAV/Modern-Cpp/tree/master/concept%20(pceudo)/detection_idiom
*/

namespace detail {
  /**
      Modern Detection Idiom: Use Fundamentals TS v2
      -----------------------------------------------
      C++ Fundamentals TS v2 provides a super easy way to use the detection idiom in C++ through std::experimental::is_detected. 
      All the user needs to do is write a template struct that checks for the attributes the user wants, then hand that off to is_detected.
      \code
         // Example
         template <typename T> using pop_back_t        = decltype(std::declval<T>().pop_back());
         template <typename T> using supports_pop_back = std::experimental::is_detected<pop_back_t, T>;

         main{
            std::cout << supports_pop_back<std::vector<int>>::value << std::endl;
            // output: true
         }
      \endcode

      \see https://people.eecs.berkeley.edu/~brock/blog/detection_idiom.php
      \see https://en.cppreference.com/w/cpp/experimental/is_detected
  */

  /**
      The alternative way how 'is_detected' can be implemented,
      rather than all of the entities which the Lib Fundamentals 2 TS provides.
      with expectation that out C++ compiler is C++17 compliant.
      \see https://blog.tartanllama.xyz/detection-idiom/
  */

   template <template <typename...> typename Trait, typename Enabler, typename... Args>
   struct is_detected : std::false_type{};

   template <template <typename...> typename Trait, typename... Args>
   struct is_detected<Trait, std::void_t<Trait<Args...>>, Args...> : std::true_type{};
}

template <template <typename...> typename Trait, typename... Args>
using is_detected = typename detail::is_detected<Trait, void, Args...>::type;

template <template <typename...> typename Trait, typename... Args>
inline constexpr bool is_detected_v = is_detected<Trait,Args...>::value;


// Usage

#include <cassert>
#include <vector>
#include <set>

template <typename Range> 
using begin_t  = decltype(std::begin(std::declval<Range>()));
template <typename Range> 
using end_t    = decltype(std::end(std::declval<Range>()));

template <typename Range> 
inline constexpr bool is_range_v = is_detected_v<begin_t,Range> && is_detected_v<end_t,Range>;

template <typename Range, typename T> 
using assignable_t  = decltype(std::declval<T&>() = *std::begin(std::declval<Range>()));

template <typename Range, typename T> 
inline constexpr bool is_assignable_v  = is_detected_v<assignable_t,Range,T>;


template< typename Range, typename T>
T accumulate( const Range& r, T init) {
   static_assert(is_range_v<Range>);
   static_assert(is_assignable_v<Range,T>);

   return std::accumulate(std::begin(r),std::end(r),init);
}

int main()
{
   const auto seq1 = {0,1,2,3,4,5,6,7,8,9};
   const auto seq2 = std::vector{0,1,2,3,4,5,6,7,8,9};
   const auto seq3 = std::set{0,1,2,3,4,5,6,7,8,9};

   assert(45 == std::accumulate(std::begin(seq1),std::end(seq1),0));
   assert(45 == std::accumulate(std::begin(seq2),std::end(seq2),0));
   assert(45 == std::accumulate(std::begin(seq3),std::end(seq3),0.f));

   assert(45 == accumulate(seq1,0));
   assert(45 == accumulate(seq2,0));
   assert(45 == accumulate(seq3,0));
}

