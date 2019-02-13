#include <iostream>
#include <variant>
#include <vector>

// The overload pattern for visitation of std::variant
// https://www.bfilipek.com/2019/02/2lines3featuresoverload.html
template<typename... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<typename... Ts> overloaded(Ts...) -> overloaded<Ts...>;

using namespace std;

struct circle
{
   const char* draw() const noexcept { return "I'm a circle"; }
   const char* foo1() const noexcept { return "circle::foo1"; }
};

struct square
{
   const char* draw() const noexcept { return "I'm a square"; }
   const char* foo2() const noexcept { return "square::foo2"; }
};

struct triangle
{
   const char* draw() const noexcept { return "I'm a triangle"; }
   const char* foo3() const noexcept { return "triangle::foo3"; }
};

using shape                      = variant<circle,square,triangle>; 
using heterogeneous_container_t  = vector<shape>; 

int main()
{
   heterogeneous_container_t shapes {circle{}, square{}, triangle{} };

   // 1. enumerate elements in the 'shapes' in OOP style (a la container of polymorphic types)
   for(auto s : shapes)
      visit([](auto s) {cout << s.draw() << endl;}, s );

   // 2. enumerate elements in the 'shapes' by means overloaded functions to distinguish every type separately
   struct visitor
   {
      void operator()(const circle& c)    { cout << c.foo1() << endl; }
      void operator()(const square& s)    { cout << s.foo2() << endl; }
      void operator()(const triangle& t)  { cout << t.foo3() << endl; }
   };
   for(auto s : shapes)
      visit(visitor{}, s );

   // 3. enumerate elements by means overloaded lambda (https://www.bfilipek.com/2019/02/2lines3featuresoverload.html)
   const auto composite_visitor = overloaded {
       [](const circle& c)   { cout << c.foo1() << endl; }
      ,[](const square& s)   { cout << s.foo2() << endl; }
      ,[](const triangle& t) { cout << t.foo3() << endl; }
   };
   for(auto s : shapes)
      visit(composite_visitor, s );
}
