#include <iostream>
#include <array>
#include <string_view>
#include <utility>

namespace v1
{
   template<typename Container, typename... Idx>
   void print(const Container& c, Idx... idx) {
      ((std::cout << c[idx]),...);
   }
}  // namespace v1

namespace v2
{
   template<size_t... Idx, typename Container>
   void print(const Container& c) {
      ((std::cout << c[Idx]),...);
   }
}  // namespace v2

namespace v3
{
   template<size_t...> struct indices {};
   template<typename Container, size_t... Idx>
   void print(const Container& c, indices<Idx...>) {
      ((std::cout << std::get<Idx>(c)),...);
   }
}  // namespace v3

namespace v4
{
   template<typename Container, size_t... Idx>
   void print(const Container& c, std::index_sequence<Idx...>) {
      ((std::cout << std::get<Idx>(c)),...);
   }
}  // namespace v4

//// Example of Usage:

using namespace std;
const array<string_view,13> arr = {
   // 0          1      2       3       4     5     6      7
   "An"," algorithm"," must"," be"," seen"," to"," be"," believed",
   "\n\t"," Donald"," Ervin"," Knuth", "\n"
   // 8         9      10        11     12
};

int main()
{
   v1::print(arr,0,1,2,3,4,5,6,7,8,9,10,11,12);
   v2::print<0,1,2,3,4,5,6,7,8,9,10,11,12>(arr);
   v3::print(arr,v3::indices<0,1,2,3,4,5,6,7,8,9,10,11,12>{});
   v4::print(arr,make_index_sequence<13>{});
}

