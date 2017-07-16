#include <string>
#include <iostream>
#include <type_traits>
#include <utility>


/**
   References:
      http://scrutator.me/post/2017/04/10/has_function_metaprogramming.aspx
      http://en.cppreference.com/w/cpp/types/void_t
*/


namespace method_1
{
   template <typename T>
   struct has_function_sort
   {
      template <typename U>
      static auto            test(U&&) -> decltype(std::declval<U>().sort(),std::true_type{});
      static std::false_type test(...);
      static constexpr bool  value = std::is_same_v<std::true_type, decltype(test(std::declval<T>()))>; 
   };

   template <typename T>
   constexpr bool has_function_sort_v = has_function_sort<T>::value;

}  // end of namespace method_1


namespace method_2
{

   template <typename T, typename = void>
   struct has_function_sort : std::false_type {};

   template <typename T>
   struct has_function_sort<T,std::void_t<decltype(std::declval<T>().sort())>> : std::true_type {};

   template <typename T>
   constexpr bool has_function_sort_v = has_function_sort<T>::value;

}  // end of namespace method_2



#include <vector>
#include <list>
#include <algorithm>
#include <iterator>

using namespace std;

template <typename ContainerT>
//enable_if_t<method_1::has_function_sort_v<ContainerT>>
enable_if_t<method_2::has_function_sort_v<ContainerT>>
sort(ContainerT& c)
{
   cout << "Calling member function: sort" << endl;
   c.sort();
}

template <typename ContainerT>
//enable_if_t<!method_1::has_function_sort_v<ContainerT>>
enable_if_t<!method_2::has_function_sort_v<ContainerT>>
sort(ContainerT& c)
{
   cout << "Calling free-standing function: std::sort" << endl;
   std::sort(std::begin(c),std::end(c));
}

int main()
{
   vector<int> vector;
   list<int> list;
   sort(vector);
   sort(list);

   std::cout << "Press any key + <enter> to exit" << std::endl;
   std::cin.get();
}
