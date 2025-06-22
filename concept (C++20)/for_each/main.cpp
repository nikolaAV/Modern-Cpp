#include <string>
#include <vector>
#include <iostream>
#include <type_traits>
#include <utility>
#include <optional>


// @brief typelist is a container for a list of types
// @see: 
template<typename... Ts> 
struct typelist {
};

// 01 create a type trait as detector for std::optional
// @see: https://stackoverflow.com/questions/62312879/boosthana-how-to-check-if-a-type-is-stdoptional
template <typename T>
struct is_optional : std::false_type {};

template <typename T>
struct is_optional<std::optional<T>> : std::true_type {};

// 02 create `Optional` concept based on the type trait above
template <typename T>
concept Optional = is_optional<std::remove_cvref_t<T>>::value;

// 03 create a generic visitor for any type which does nothing
template<typename T>
consteval void visit(size_t&) {
}

// 03.01 create a constrained visitor by Optional concept which increments counter
template<Optional T>
consteval void visit(size_t& value) {
   value++;
}

// 04 create `for_each` function that takes a typelist and applies the visitor to each item in it
template<typename... Ts> 
consteval size_t for_each(typelist<Ts...>) {
   size_t res = 0;
   (visit<Ts>(res),...);
   return res;
}

int main()
{
   using list = typelist<
       int
      ,double
      ,std::optional<std::vector<unsigned>>
      ,char
      ,std::string
      ,std::optional<long>
   >;

   // 05 usage
   constexpr auto num = for_each(list{});
   std::cout << num << std::endl;
}

