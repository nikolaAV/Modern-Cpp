# Compile time computing of the greatest common divisor.
Since C++17, the Standard Library provides `constexpr` algorithm [`std::gcd`](https://en.cppreference.com/w/cpp/numeric/gcd) which accepts two integers.
This algorithm can be extended for more than two ones. The GCD of three or more numbers equals the product of the prime factors common to all the numbers, but it can also be calculated by repeatedly taking the GCDs of pairs of numbers.
```cpp
gcd(a, b, c) = gcd(a, gcd(b, c))
```
Using variadic parameter list, the function can be defined:
```cpp
template <typename T, typename... U>
constexpr auto gcd(T m, U... ns)
{
   return gcd(m,gcd(ns...));
}

template <typename T>
constexpr auto gcd(T m, T n)
{
   return std::gcd(m,n);
}
```
Example of usage:
```cpp
  static_assert(8==gcd(48,16,24,96));
  static_assert(1==gcd(1,2,3));
  static_assert(2==gcd(8,6,4,2,10,12,100));
```
There is also overloaded version for C arrays:
```cpp
  constexpr long arr[] = {48,16,24,96};
  static_assert(8==gcd(arr));
```

Implementation above is based on recursion. Since C++17 when [`constexpr` lambda](../../lambda/lambda_constexpr) has been introduced, there is no limitation to provide solution in imperative style.  
First, we have to write a `constexpr` analog of [std::accumulate](https://en.cppreference.com/w/cpp/algorithm/accumulate).
```cpp
template<typename Range, typename Func, typename T>
constexpr T accumulate(const Range& range, Func func, T init) {
   for(auto&& elem:range)
      init = func(init,elem);
   return init; 
}
```
then 'gcd' implementation may be as follow:
```cpp
template<typename Range>
constexpr auto gcd(const Range& range) {
   return accumulate(range
      ,[](auto x, auto y){ return -1==x? y : std::gcd(x,y); }
      ,-1      
   );
}
```

## Further informations
* [Greatest common divisor of more than two numbers](https://math.stackexchange.com/questions/1672249/greatest-common-divisor-of-more-than-two-numbers)
* [Euclidean algorithm](https://en.wikipedia.org/wiki/Euclidean_algorithm)

## Related links
* [Other examples of compile time computing](../)
* [std::lcm](https://en.cppreference.com/w/cpp/numeric/lcm)
* [run-time gcd](https://github.com/nikolaAV/skeleton/tree/master/algorithm/gcd)

## Compilers
* [GCC 8.1.0](https://wandbox.org/)
* [clang 7.0.0](https://wandbox.org/)
* Microsoft (R) C/C++ Compiler 19.16 
