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

### Other examples of compile time computing
* [Greatest common divisor](./greatest_common_divisor)
* [String hash](https://github.com/nikolaAV/skeleton/tree/master/switch_string)
* [Cartesian product](../lambda/lambda_cartesian)
* [Inner product](../lambda/lambda_inner)
* [String concatenation](https://github.com/nikolaAV/skeleton/tree/master/static_string)
* [min & max for any number of arguments](./min_max)
* [Validating ISBNs](./isbn)
* [accumulate algorithm with constexpr lambda](../lambda/lambda_constexpr)
* `constexpr` [helps us detect](https://www.walletfox.com/course/cheatsheetsSource/constexpr_undefined.png) (taken from @walletfox) [undefined behaviour](https://en.cppreference.com/w/cpp/language/ub).
* [`std::tuple<chars...>` initialized with pure C string literals](../tuple/init_from_string_literal)

## Further informations
* [constexpr specifier](https://en.cppreference.com/w/cpp/language/constexpr)

## Related links
* [`constexpr` invocation context](./invocation_context)

## Compilers
`constexpr` feature was introduced in _C++11_ and extended in _C++14_,_C++17_.
