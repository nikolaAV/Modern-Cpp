#include <iostream>
#include <string>
#include <type_traits>

/**
   How To Detect Function Overloads in C++17
   The problem: a library function offers several overloads, 
   but depending on the implementation/compiler, 
   some of the overloads are not available. 
   How to check the existence of an overload? 
   And how to provide a safe fallback?

   \see https://www.bfilipek.com/2019/07/detect-overload-from-chars.html
*/

namespace library // let's suppose it's a third-party library
{
   void compute(double in, double& out)   { out = in; }
   void compute(long in,   long& out)     { out = in; }
// void compute(short in, short& out)     { out = in; }

}  // end of namespace library



/**
   C++ Detection Idiom
   \see https://github.com/nikolaAV/Modern-Cpp/tree/master/concept%20(pceudo)/detection_idiom
*/
template <typename T>
using compute_t = decltype(library::compute(std::declval<T>(), std::declval<T&>()));

template <typename T, typename = void>
struct is_compute_available : std::false_type {};

template <typename T>
struct is_compute_available<T,std::void_t<compute_t<T>>> : std::true_type {};

template <typename T>
inline bool constexpr is_compute_available_v = is_compute_available<T>::value;

template <typename T>
void custom_compute(T in, T& out) {
   double tmp{};
   library::compute(in,tmp);
   out = static_cast<T>(tmp);
}

template <typename T>
T compute(T in) {
   T out{};
   if constexpr(is_compute_available_v<T>) {
//      std::cout << "library::compute"; 
      library::compute(in,out);
   } else {
//      std::cout << "custom_compute";
      custom_compute(in, out);
   }
   return out;
}

int main()
{
   static_assert(is_compute_available_v<long>);
   static_assert(is_compute_available_v<double>);
   static_assert(!is_compute_available_v<float>);
   static_assert(!is_compute_available_v<short>);

   std::cout << "double: " << compute(3.14) << "; int: " << compute(1) << std::endl;
}
