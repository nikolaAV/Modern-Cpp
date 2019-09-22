#include <type_traits>
#include <utility>

/**
   Predicate Composition

   see https://youtu.be/PFdWqa68LmA?t=2080 by Stephen Dewhurst

*/

template <typename T>
using is_not_polymorphic = std::negation<std::is_polymorphic<T>>;

namespace std17 {

   template<typename T>
   inline constexpr bool Happy_v = std::conjunction_v<
       std::is_class<T>
      ,std::is_nothrow_default_constructible<T>
      ,std::is_nothrow_copy_constructible<T>
      , is_not_polymorphic<T>
   >;

}  // end of std17


namespace cpp11 {
   // Traditional First/Rest Recursive Implementation

   template <template <typename...> class... Preds>
   struct Compose;

   template <template <typename...> class First, template <typename...> class... Rest>
   struct Compose<First,Rest...> {
      template <typename T>
      static constexpr auto value() {
         return First<T>::value && Compose<Rest...>::template value<T>();
      }
   };

   template <>
   struct Compose<> {
      template <typename T>
      static constexpr auto value() {
         return true;
      }
   };

   using Happy = Compose<
       std::is_class
      ,std::is_nothrow_default_constructible
      ,std::is_nothrow_copy_constructible
      ,is_not_polymorphic
   >;

   template<typename T>
   inline constexpr bool Happy_v = Happy::value<T>();

}  // end of cpp11

namespace cpp14 {
   // Simplier Non-Recursive Implementation

   template <template <typename...> class... Preds>
   struct Compose {
      template <typename T>
      static constexpr auto value() {
         for(auto i: { Preds<T>::value... })
            if(!i) return false;
         return true;
      }
   };

   using Happy = Compose<
      std::is_class
      ,std::is_nothrow_default_constructible
      ,std::is_nothrow_copy_constructible
      ,is_not_polymorphic
   >;

   template<typename T>
   inline constexpr bool Happy_v = Happy::value<T>();

} // end of cpp14

namespace cpp17 {
   // the simpliest by means fold expression

   template<typename T, template <typename...> class... Ts>
   inline constexpr bool Composer = (...&&Ts<T>::value);

   template<typename T>
   inline constexpr bool Happy_v = Composer<T,
       std::is_class
      ,std::is_nothrow_default_constructible
      ,std::is_nothrow_copy_constructible
      ,is_not_polymorphic
   >;

} // end of cpp17

// Example of usage

#include <string>
#include <stdexcept>

using namespace std;

struct A {};
struct B {virtual void foo() {}};

void test_std17()
{
   using namespace std17;

   static_assert(!Happy_v<string>, "Unhappy, I am std::string");
   static_assert(Happy_v<true_type>, "Unhappy, I am std::true_type");
   static_assert(!Happy_v<out_of_range>, "Unhappy, I am std::out_of_range");
   static_assert(Happy_v<A>, "Unhappy, I am A");
   static_assert(!Happy_v<B>, "Unhappy, I am B");
}

void test_cpp11()
{
   using namespace cpp11;

   static_assert(!Happy_v<string>, "Unhappy, I am std::string");
   static_assert(Happy_v<true_type>, "Unhappy, I am std::true_type");
   static_assert(!Happy_v<out_of_range>, "Unhappy, I am std::out_of_range");
   static_assert(Happy_v<A>, "Unhappy, I am A");
   static_assert(!Happy_v<B>, "Unhappy, I am B");
}

void test_cpp14()
{
   using namespace cpp14;

   static_assert(!Happy_v<string>, "Unhappy, I am std::string");
   static_assert(Happy_v<true_type>, "Unhappy, I am std::true_type");
   static_assert(!Happy_v<out_of_range>, "Unhappy, I am std::out_of_range");
   static_assert(Happy_v<A>, "Unhappy, I am A");
   static_assert(!Happy_v<B>, "Unhappy, I am B");
}

void test_cpp17()
{
   using namespace cpp17;

   static_assert(!Happy_v<string>, "Unhappy, I am std::string");
   static_assert(Happy_v<true_type>, "Unhappy, I am std::true_type");
   static_assert(!Happy_v<out_of_range>, "Unhappy, I am std::out_of_range");
   static_assert(Happy_v<A>, "Unhappy, I am A");
   static_assert(!Happy_v<B>, "Unhappy, I am B");
}

int main()
{
}
