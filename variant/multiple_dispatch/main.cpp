#include <iostream>
#include <variant>

/**
   How To Use std::visit With Multiple Variants
   \see https://www.bfilipek.com/2018/09/visit-variants.html
*/

using namespace std;

struct circle     {};
struct square     {};
struct triangle   {};

void intersect(const circle&, const circle&) {
   cout << "circle <-> circle" << endl;
}

void intersect(const circle&, const square&) {
   cout << "circle <-> square" << endl;
}

void intersect(const circle&, const triangle&) {
   cout << "circle <-> triangle" << endl;
}

void intersect(const square&, const square&) {
   cout << "square <-> square" << endl;
}

void intersect(const square&, const circle&) {
   cout << "square <-> circle" << endl;
}

void intersect(const square&, const triangle&) {
   cout << "square <-> triangle" << endl;
}

void intersect(const triangle&, const triangle&) {
   cout << "triangle <-> triangle" << endl;
}

void intersect(const triangle&, const circle&) {
   cout << "triangle <-> circle" << endl;
}

void intersect(const triangle&, const square&) {
   cout << "triangle <-> square" << endl;
}

using shape  = variant<circle,square,triangle>; 
void intersect(const shape& left, const shape& right) {
   visit(
      [](auto s1, auto s2) { intersect(s1,s2); }
      ,left,right
   );
}

shape factory(size_t id) {
   switch(id) {
      case 1 : return square{};
      case 2 : return triangle{};
   }
   return circle{};
}


int main()
{
   const auto s0 = factory(0);
   const auto s1 = factory(1);
   const auto s2 = factory(2);

   intersect(s0,s1);
   intersect(s1,s2);
   intersect(s2,s0);
}
