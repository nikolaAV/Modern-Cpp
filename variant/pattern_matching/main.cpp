#include <iostream>
#include <variant>
#include <utility>
#include <cmath>

/**
   C++17 Pattern matching with std::variant, std::monostate and std::visit
   \see https://www.walletfox.com/course/patternmatchingcpp17.php

   This example presents the solution of a quadratic equation, which has either 2, 1 or 0 roots in the real number domain.
   A non-existent solution is represented by std::monostate() which is used for cases when std::variant does not contain a value.
*/


// https://github.com/nikolaAV/Modern-Cpp/tree/master/lambda/lambda_overloaded
template<typename... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<typename... Ts> overloaded(Ts...)->overloaded<Ts...>;

using _1root_type  = double;
using _2roots_type = std::pair<double,double>;
using _0root_type  = std::monostate;
using result_type  = std::variant<_0root_type, _1root_type, _2roots_type>;

result_type compute(double a, double b, double c) noexcept {
   const auto discriminant = b*b-4*a*c;
   const auto denominator  = 2*a;
   if (0. < discriminant) {
      const auto square       = std::sqrt(discriminant);
      return _2roots_type{(-b+square)/denominator,(-b-square)/denominator};
   }
   if (0. == discriminant)
      return _1root_type{-b/denominator};
   return _0root_type{};
}

std::ostream& operator<<(std::ostream& out, const result_type& r) {
   std::visit(overloaded{
          [&](const _2roots_type& v) { out << "2 real roots found: " << v.first << "," << v.second; }
         ,[&](const _1root_type& v)  { out << "1 real root found: " << v; }
         ,[&](const _0root_type& v)  { out << "no real root found"; }
   },r);
   return out;
}

int main()
{
   using namespace std;

   cout << compute(1,3,-4)    << endl;     // {1,-4}
   cout << compute(-6,-5,-1)  << endl;     // {-1/2,-1/3}
   cout << compute(1,-4,0)    << endl;     // {4,0}
   cout << compute(1,0,-9)    << endl;     // {3,-3}
   cout << compute(1,12,36)   << endl;     // {-6}
   cout << compute(5,3,7)     << endl;     // {}
}
