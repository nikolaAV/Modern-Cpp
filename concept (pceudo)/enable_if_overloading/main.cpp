   #include <type_traits>
   #include <iostream>

/**
   Version v00, initial
   Function template defined with anonymous (unnamed) template parameter.
   Overload resolution cannot be done
   compiler error: 'T foo(T)': function template has already been defined

   \see  http://codeofthedamned.com/index.php/enable_if
         https://www.fluentcpp.com/2018/05/18/make-sfinae-pretty-2-hidden-beauty-sfinae/

namespace v00
{
   template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
   T foo(T v)
   {
      return v;
   }

   template <typename T, typename = std::enable_if_t<!std::is_integral_v<T>>>
   T foo(T v)
   {
      return v;
   }

   // compiler error: 'T v1::foo(T)': function template has already been defined

} // namespace v00
*/

/**
   Version 01
   Function returns std::enable_if<>::type. 
   Overloading is Ok
*/
namespace v01
{
   template <typename T>
   std::enable_if_t<std::is_integral_v<T>,T>
   foo(T v)
   {
      std::cout << "specific case (integer): " << v << std::endl;
      return v;
   }

   template <typename T>
   std::enable_if_t<!std::is_integral_v<T>,T>
   foo(T v)
   {
      std::cout << "common case: " << v << std::endl;
      return v;
   }

}  // namespace v01


/**
   Version 02
   Function accepts a default parameter of type that deduced by std::enable_if<>. 
   Overloading is Ok
*/
namespace v02   // 
{
   template <typename T>
   T foo(T v, std::enable_if_t<std::is_integral_v<T>,T>* = nullptr)
   {
      std::cout << "specific case (integer): " << v << std::endl;
      return v;
   }
   
   template <typename T>
   T foo(T v, std::enable_if_t<!std::is_integral_v<T>,T>* = nullptr)
   {
      std::cout << "common case: " << v << std::endl;
      return v;
   }

}  // namespace v02

/**
   Version 03
   Template function defined with default anonymous (unnamed) template parameter. 
   That is an outcome of combination two approaches: v00, v02 
   Overloading is Ok
*/
namespace v03   // 
{
   template <typename T, std::enable_if_t<std::is_integral_v<T>,T>* = nullptr>
   T foo(T v)
   {
      std::cout << "specific case (integer): " << v << std::endl;
      return v;
   }
   
   template <typename T, std::enable_if_t<!std::is_integral_v<T>,T>* = nullptr>
   T foo(T v)
   {
      std::cout << "common case: " << v << std::endl;
      return v;
   }

}  // namespace v03

int main()
{
   using namespace std;
   using namespace v03; // try also v01, v02

   foo(1);
   foo(3.14159);
   foo("text");
}
