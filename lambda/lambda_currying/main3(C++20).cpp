#include <tuple>
#include <utility>
#include <type_traits>
#include <functional>

constexpr decltype(auto) make_curried(auto func, auto... args)
{
   if constexpr ( requires { std::invoke(func, args...); } )
   {
      return std::invoke(func, args...);
   }
   else
   {
      return [func, args...] (auto... rest) -> decltype(auto) {
         return make_curried(func, args..., rest...);
      };
   }
}

////// 

#include <iostream>

void foo(int a1, int a2, int a3, int a4, int a5)
{
   std::cout << "foo:"
      << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5
      << std::endl;
}

int main()
{
   foo(1,2,3,4,5);   
   {
      auto const c = make_curried(foo);
      c(11)(12)(13)(14)(15);
   }
   {
      auto const c = make_curried(foo,21,22);
      c(23)(24,25);
   }
}

