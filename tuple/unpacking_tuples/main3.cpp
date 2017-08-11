#include <string>
#include <iostream>
#include <cassert>
#include "tuple_utils.h"

using namespace std;

// 0. Let's suppose there is a function with signatute: T fn(Arg1,Arg2,...)
// 1. we need to delegate it for further invocation: T delegate(fn,Arg1,Arg2,...)
// 2. so, we pack input arguments (Arg1,Arg2,...) into a singular object of std::tuple<Arg1,Arg2,...> type
// 3. create a lambda expression ( signature -> T(void) ) which
//    3.1 captures input argument pack (tuple) by means moving(!!!)
//    3.2 unpack the tuple in lambda's body
//    3.3 call the original fn
//    3.4 returns the value returned by the fn  


template <typename Function, typename... Args>
inline 
decltype(auto)
delegate_call(Function&& f, Args&&... args)
{
   // lambda signatute: T(void)
   auto lambda = [f=std::move(f),a=std::make_tuple(std::forward<Args>(args)...)]() { 
      return tu::apply(std::move(f),std::move(a));
   };
   // this lambda can be moved into suitable place where it can be triggered later
   // ...
   return lambda();
}

void foo0() {}

int  foo1(int v) { return v; }

auto foo2(int& v1, int& v2) 
{
   const auto r = make_pair(v1,v2);
   v1 = v2 = 0;
   return r;
}

int main3()
{
   delegate_call(foo0);

   auto r1 = delegate_call(foo1,23);
   assert(23==r1);

   int v1{1}, v2{2};
   auto r2 = delegate_call(foo2,ref(v1),ref(v2));
   assert(1==r2.first && 2==r2.second);
   assert(0==v1 && 0==v2);

   cout << "press <enter> key" << endl;
   cin.get();
   return 0;
}
