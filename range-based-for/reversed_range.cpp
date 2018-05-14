#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <initializer_list>

/**
   reversed range-based for-loop
   https://stackoverflow.com/questions/8542591/c11-reverse-range-based-for-loop
   https://www.boost.org/doc/libs/1_56_0/libs/range/doc/html/range/reference/adaptors/reference/reversed.html
*/

namespace range_adaptor
{
   template <typename T> struct reversed_range {T& range_;};
   template <typename T> auto   begin(reversed_range<T> wrap) { return std::rbegin(wrap.range_); }
   template <typename T> auto   end(reversed_range<T> wrap)   { return std::rend(wrap.range_); }

   template <typename T> reversed_range<T> 
   reversed(T&& r)                         noexcept { return  {r}; }
   template <typename T> reversed_range<std::initializer_list<T>> 
   reversed(std::initializer_list<T>&& r)  noexcept { return  {r}; }

}  // range_adaptor

using namespace std;
using namespace range_adaptor;

void test1()
{
   for(auto val:{1,2,3,4,5,6,7,8,9})
      cout << val;
   cout << endl;
   for(auto val:reversed({1,2,3,4,5,6,7,8,9}))
      cout << val;
   cout << endl;
}

void test2()
{
   const vector<unsigned char> v {'a','b','c','d','e','f','g'};   
   for(auto val:v)
      cout << val;
   cout << endl;
   for(auto val:reversed(v))
      cout << val;
   cout << endl;
}

void test3()
{
   vector<int> dest;
   const auto src = reversed({9,8,7,6,5,4,3,2,1,0});
   copy(begin(src),end(src),inserter(dest,end(dest)));
   for(auto val:dest)
      cout << val;
   cout << endl;
}

int main()
{
   test1();
   test2();
   test3();
}