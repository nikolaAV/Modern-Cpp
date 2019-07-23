#include <optional>
#include <utility>

/**
   Expressiveness, Nullable Types, and Composition

   \see https://www.fluentcpp.com/2019/07/16/expressiveness-nullable-types-and-composition-part-1/
        https://www.bfilipek.com/2018/06/optional-examples-wall.html
        https://github.com/rvarago/absent
        https://github.com/nikolaAV/Modern-Cpp/tree/master/stl/optional#example-2-chain-building-for-function-calls
*/

namespace monad
{
   /**
      It implements monadic bind operation that chain functions together without explicitly checking errors.      

      \see https://en.wikipedia.org/wiki/Monad_%28functional_programming%29
   */
   template <typename Arg, typename Mapper>
   auto bind(std::optional<Arg> input, Mapper fn) -> decltype(fn(std::declval<Arg>())) {
      return input.has_value()? fn(std::move(*input)) : std::nullopt;
   }

   /**
      The basic idea of ability to build of a chain operations that return std::optional 
      can be expressed more clearly by overloading operator>>
      then  B fA(B), C fB(B), D fC(C) can be callable as a chain of calls
      auto d = B >> fA >> fB >> fC;
   */
   template <typename Arg, typename Mapper>
   auto operator>>(std::optional<Arg> input, Mapper fn) {
      return bind(input,fn);
   }
}  // end of namespace monad

////////// Usage Example
#include <tuple>
#include <iostream>

using namespace std;

struct zip_code { const char* value = "zip: Ok"; };
struct address {};
struct person {};
struct query { bool empty = false; };

optional<query>    get_query(bool test_positive=false)   { return query{!test_positive}; }
optional<person>   get_person(const query& q)            { return q.empty? optional<person>{} : optional{person{}}; }
optional<address>  get_address(const person&)            { return address{}; }
optional<zip_code> get_zip_code(const address&)          { return zip_code{}; }


void test_1(bool positive)
{
   const auto q = get_query(positive);
   if (!q) return;
   const auto p = get_person(*q);
   if (!p) return;
   const auto a = get_address(*p);
   if (!a) return;
   const auto z = get_zip_code(*a);
   if (!z) return;

   // use z
   cout << (*z).value << endl;
}

void test_2(bool positive)
{
   /**
      Thanks to the short circuit rules and the evaluation happening from left to right 
      the functions won’t be executed if the previous one fails when a function returns empty std::variant.
      \see https://en.cppreference.com/w/cpp/language/operator_logical
           https://en.wikipedia.org/wiki/Short-circuit_evaluation
   */

   // https://github.com/nikolaAV/Modern-Cpp/tree/master/structured-bindings/direct_initialization
   if(auto [q,p,a,z]= tuple{optional<query>{},optional<person>{},optional<address>{},optional<zip_code>{}};
         (q = get_query(positive))
      && (p = get_person(*q))
      && (a = get_address(*p))
      && (z = get_zip_code(*a))
   )
      cout << (*z).value << endl;
   else
      cout << "Error: zip_code cannot be obtained." << endl;
}

void test_3(bool positive)
{
   using namespace monad;

   if (auto z = optional{positive} >> get_query >> get_person >> get_address >> get_zip_code)
      cout << (*z).value << endl;
   else
      cout << "Error: zip_code cannot be obtained." << endl;
}

int main()
{
   test_1(true);
   test_1(false);
   test_2(true);
   test_2(false);
   test_3(true);
   test_3(false);
}
