#include <string>
#include <iostream>
#include <algorithm>
#include <cassert>
#include "tuple_utils.h"


int sum(int a0, int a1, int a2, int a3)
{
   return  a0 + a1 + a2 + a3;
}

struct sum3
{
   int value = 0;
   void operator()(int v) { value += v; }
};

int main()
{

   auto t1 = tu::take_front<2>(std::make_tuple(1, 2, 3, 4));
   assert(t1 == std::make_tuple(1, 2));

   auto t2 = tu::take_back<2>(std::make_tuple(1, 2, 3, 4));
   assert(t2 == std::make_tuple(4, 3));

   auto t3 = tu::reverse(std::make_tuple(1, 2, 3, 4));
   assert(t3 == std::make_tuple(4, 3, 2, 1));

   auto t4 = tu::apply(sum,std::make_tuple(1, 2, 3, 4));
   assert(10 == t4);

   size_t sum2=0;
   tu::for_each([&sum2](auto v) { sum2 += v; } ,std::make_tuple(1, 2, 3, 4));
   assert(10 == sum2);

   auto t5 = tu::for_each(sum3{},std::make_tuple(1, 2, 3, 4));
   assert(10 == t5.value);

   std::cout << "Press any key + <enter> to exit" << std::endl;
   std::cin.get();
}
