# constexpr.
Compile-time computations can be realized in two ways: backward compatible with template meta-functions or more easily with `constexpr`. 
Compile-time functions are almost as expressive as regular functions. As a technical example we can realize _'popcount'_ (short for population count) which counts the number of 1-bits in binary data:
```cpp
constexpr size_t popcount(size_t x) {
   int count= 0;
   for (; x != 0; ++count)
   x&= x - 1;
   return count;
}
```
This code is allowed in _C++14_ but not in _C++11_. The function can be expressed in _C++11_ `constexpr` as well and is even shorter in the recursive formulation:
```cpp
constexpr size_t popcount(size_t x) {
   return x == 0 ? 0 : popcount(x & x-1) + 1;
}
```
This stateless, recursive computation might be less comprehensible for some readers, and maybe clearer to others. It is said that finding iterative or recursive programs easier to understand depends on the order in which they are introduced to a programmer.
Fortunately, C++ let us implement both.


## Further informations
* [constexpr specifier](https://en.cppreference.com/w/cpp/language/constexpr)

## Related links
* [hash compile time computation](https://github.com/nikolaAV/skeleton/tree/master/switch_string)

## Compilers
`constexpr` feature was introduced in _C++11_ and extended in _C++14_.