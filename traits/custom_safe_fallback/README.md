# Checking the existence of a function and the custom safe fallback 
The problem: a library function offers several overloads, but depending on the implementation/compiler, some of the overloads are not available. How to check the existence of an overload? And how to provide a safe fallback?  
Imagine there is a third-party library that provides a function:
```cpp
// version v.01
void compute(double in, double& out);
```
Later in the second version of the library, some new overloads can be also provided:
```cpp
// version v.02
void compute(double in, double& out);
void compute(long in, long& out);
void compute(short in, short& out);
...
```
The problem is that on the application level we want to have support all overloads (`double`,`long`,`short`,etc.) in out project __no matter what’s the version of the library used__. 
In a case, if the library version does not contain a necessary overload we have to provide a custom alternative. How it can be done more effectively?  
What we need is a way to ask the compiler:
```cpp
template <typename T>
T my_compute(T in) {
   T out{};
   if constexpr(is_compute_available_v<T>)
      compute(in,out);     // the library supports it
   else { // custom alternative here
          // ...
   }
   return out;
}
```
where 'is_compute_available_v<T>' - it is a compile time variable which gives the answer whether function 'compute' for requested type exists or not.
```cpp
template <typename T>
using compute_t = decltype(compute(std::declval<T>(), std::declval<T&>()));

template <typename T, typename = void>
struct is_compute_available : std::false_type {};

template <typename T>
struct is_compute_available<T,std::void_t<compute_t<T>>> : std::true_type {};

template <typename T>
inline bool constexpr is_compute_available_v = is_compute_available<T>::value;
```

## Further informations
* [How To Detect Function Overloads in C++17](https://www.bfilipek.com/2019/07/detect-overload-from-chars.html)
## Related links
* [C++ Detection Idiom](../../concept%20(pceudo)/detection_idiom)

## Compilers
* [GCC 8.1.0](https://wandbox.org/)
* [clang 7.0.0](https://wandbox.org/)
* Microsoft (R) C/C++ Compiler 19.14 
