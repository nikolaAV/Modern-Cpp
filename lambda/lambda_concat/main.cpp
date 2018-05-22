#include <iostream>
#include <cmath>

namespace composite
{

struct start_tag {
   template <typename param>
   decltype(auto) operator()(param p) const {
      return p;
   } 
};

auto start = start_tag{};

template <typename L, typename R>
struct compose_fn {
   L l; R r;
   template <typename... params>
   decltype(auto) operator()(params... ps) const {
      return l(r(ps...));
   } 
};

template <typename L, typename R>
compose_fn<L,R> compose(L l, R r) {
   return {l,r};   
}

template <typename... Ls, typename R>
decltype(auto) operator | (compose_fn<Ls...> l, R r) {
   return compose(r,l);
}


template <typename R>
decltype(auto) operator | (start_tag l, R r) {
   return compose(l,r);
}

} // end of namespace: composite

using namespace std;

int main()
{
   /**
      mathematical statement:
       ________
      v(x+y)*2     
   */

   auto sum    = [](auto x, auto y) { return x+y; };   
   auto twice  = [](auto x)         { return 2*x; };
   auto sqrt   = [](auto x)         { return std::sqrt(x); };

   auto formula = composite::start | sum | twice | sqrt;
   cout << formula(4,5) << endl;
   cout << formula(3.14,2.56) << endl;
}
