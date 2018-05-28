#include <iostream>
#include <cmath>

namespace composite
{

template <typename L, typename R>
auto concat(L l, R r) {
   return [=](auto... params) {
      return l(r(params...));
   };
}

template <typename L, typename R>
auto operator | (L l, R r) {
   return concat(r,l);
}

} // end of namespace: composite

using namespace std;

int main()
{
   /**
      mathematical statement:
       ________
      v(x+y+z)*2     
   */

   auto sum    = [](auto x, auto y, auto z)  { return x+y+z; };   
   auto twice  = [](auto x)                  { return 2*x; };
   auto sqrt   = [](auto x)                  { return std::sqrt(x); };

   using namespace composite;
   auto formula = sum | twice | sqrt;
   cout << formula(4,5,6) << endl;
   cout << formula(3.14,2.56,0.1) << endl;
}
