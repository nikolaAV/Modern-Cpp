# Compile time 'min' & 'max' functions with any number of arguments.
Since C++17, the Standard Library provides `constexpr` algorithms [`std::min`](https://en.cppreference.com/w/cpp/algorithm/min) and [`std::max`](https://en.cppreference.com/w/cpp/algorithm/max) that accept two parameters.
They can be extended for any arguments against only two.
It is possible to write function templates that can take a variable number of arguments using variadic function templates.
For this, we need to implement compile-time recursion (which is actually just calls through a set of overloaded functions).
The following snippet shows how the requested 'min' function could be implemented
```cpp
template <typename T>
constexpr T min(T a, T b)
{
    return std::min(a,b);
}

template <typename T, typename... U>
constexpr T min(T a, T... bs)
{
   return min(a, min(bs...));
}
```
and the usage is:
```cpp
int main()
{
   static_assert(0==min(0,1,2,3,4,5,6,7,8,9));
   static_assert(1==min(2,1));
   static_assert(9==max(0,1,2,3,4,5,6,7,8,9));
   static_assert(2==max(2,1));
}
```

## Further informations
* [`std::min`](https://en.cppreference.com/w/cpp/algorithm/min)
* [`std::max`](https://en.cppreference.com/w/cpp/algorithm/max)

## Related links
* [Other examples of compile time computing](../)

## Compilers
* [GCC 8.1.0](https://wandbox.org/)
* [clang 6.0.1](https://wandbox.org/)
* Microsoft (R) C/C++ Compiler 19.16 
