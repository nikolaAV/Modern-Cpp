#include <optional>
#include <type_traits>
#include <utility>

/**
   One more approach we can take implementing 'Fizz buzz' game 
   by means 'std::optional' feature included in Modern C++ (C++17).

   see https://www.fluentcpp.com/2019/08/20/a-concise-implementation-of-fizzbuzz-with-stdoptional/
       https://en.wikipedia.org/wiki/Fizz_buzz
*/

/**
   operator+(std::optional<T> left, std::optional<T> right)
   Computes the sum of the two values held by std::optional.
   It uses operator+(T,T) to sum up the values which are of the same type
   where T is the type for which std::optional<T> is instantiated. 

   \param left, right input exemplars of std::optional<T> to sum up
   \retval sum of *left and *right inclosed into std::optional if both left and right is not nullopt. 
           Otherwise, if the input argument does not contain a value it's ignored during computation.
   \code
      auto res1 = std::optional{1} + std::optional{2};
      assert(3==*res1);
      auto res2 = std::optional{} + std::optional{2};
      assert(2==*res2);
   \endcode
*/

namespace concepts {

   template <typename T, typename = void>
   struct is_addition_supported : std::false_type {};

   template <typename T>
   struct is_addition_supported<T, std::void_t<decltype(std::declval<T>() + std::declval<T>())>>
                                : std::true_type {};
   template<typename T>
   inline constexpr bool is_addition_supported_v = is_addition_supported<T>::value;

} // end namespace concepts

template <typename T>
auto operator+(const std::optional<T>& left, const std::optional<T>& right) {
   static_assert(concepts::is_addition_supported_v<T>, "no match for T+T");
   if(left && right)
      return std::make_optional(*left + *right);
   return left? left : right; 
}

// Example of usage

#include <cassert>
#include <string>

using namespace std;
using namespace std::literals::string_literals;

string fizzbuzz(size_t n) {
   const auto if_factor = [n](size_t divisor, const string& s) {
      return (n%divisor)==0? make_optional(s) : nullopt;
   };
   return (if_factor(3,"Fizz") + if_factor(5, "Buzz")).value_or(to_string(n));
}


void test_addition()
{
   assert(8 == *(optional{ 5 }+optional{ 3 }));
   assert(5 == *(optional{ 5 }+optional<int>{}));
   assert(!(optional<int>{}+optional<int>{}));
   assert(*(optional{ "5"s }+optional{ "3"s }) == "53");
   assert(*(optional<string>{}+optional{ "3"s }) == "3");
   assert(!(optional<string>{}+optional<string>{}));
   // assert(*(optional{"5"}+optional{"3"})); // <--- static_assert("5"+"3") fails
}

void test_fizzbuzz()
{
   assert(fizzbuzz(1)=="1");
   assert(fizzbuzz(2)=="2");
   assert(fizzbuzz(3)=="Fizz");
   assert(fizzbuzz(4)=="4");
   assert(fizzbuzz(5)=="Buzz");
   assert(fizzbuzz(15)=="FizzBuzz");
}

int main()
{
   test_addition();
   test_fizzbuzz();
}
