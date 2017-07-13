#include <string>
#include <iostream>
#include <variant>
#include <vector>

using namespace std;

struct circle
{
   const char* draw() const { return "I'm a circle"; }
   const char* foo1() const { return "circle::foo1"; }
};

struct square
{
   const char* draw() const { return "I'm a square"; }
   const char* foo2() const { return "square::foo2"; }
};

struct triangle
{
   const char* draw() const { return "I'm a triangle"; }
   const char* foo3() const { return "triangle::foo3"; }
};

using shape                      = variant<circle,square,triangle>; 
using heterogeneous_container_t  = vector<shape>; 

int main()
{
   heterogeneous_container_t shapes {circle{}, square{}, triangle{} };

   // enumerate elements in the 'shapes' in OOP style (a la container of polymorphic types)
   for(auto s : shapes)
      visit([](auto s) {cout << s.draw() << endl;}, s );

   // enumerate elements in the 'shapes' by means overloaded functions to distinguish every type separately
   struct visitor
   {
      void operator()(const circle& c)    { cout << c.foo1() << endl; }
      void operator()(const square& s)    { cout << s.foo2() << endl; }
      void operator()(const triangle& t)  { cout << t.foo3() << endl; }
   };
   for(auto s : shapes)
      visit(visitor{}, s );

   std::cout << "Press any key + <enter> to exit" << std::endl;
   std::cin.get();
}
