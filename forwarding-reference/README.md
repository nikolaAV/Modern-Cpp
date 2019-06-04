# std::forward

In template code, we often use [`std::forward`](https://en.cppreference.com/w/cpp/utility/forward) since C++11, to pass values along without losing the fact that they are `l-value` or `r-value` references:
```cpp
template<typename T1, typename T2>
void foo(T1&& arg1, T2&& arg2){
    \\ ...
    bar(std::forward<T1>(arg1), std::forward<T2>(arg2));
}
```
The && in this template code means that the values can be `l-value` or `r-value` references depending on whether the values they bind to are `l-values` or `r-values`.
`std::forward` allows to pass on this information to __bar__.  
But it’s a lot of code to express that, it’s annoying to type every time, and it takes up some space when reading.  
To reducing this "noise" [Vittorio Romeo proposes](https://vittorioromeo.info/index/blog/capturing_perfectly_forwarded_objects_in_lambdas.html) to use the following macro:
```cpp
#define FWD(...) ::std::forward<decltype(__VA_ARGS__)>(__VA_ARGS__)
```
Here is how the previous code now looks like by using it:
```cpp
template<typename T1, typename T2>
void foo(T1&& arg1, T2&& arg2){
    \\ ...
    bar(FWD(arg1), FWD(arg2));
}
```
The macro made the code easier to type and read.

## Further Informations
* [Universal References in C++11](https://isocpp.org/blog/2012/11/universal-references-in-c11-scott-meyers) by Scott Meyers
* [Perfect forwarding and universal references in C++](http://eli.thegreenplace.net/2014/perfect-forwarding-and-universal-references-in-c/) by Eli Bendersky
* [Capturing perfectly-forwarded objects in lambdas](https://vittorioromeo.info/index/blog/capturing_perfectly_forwarded_objects_in_lambdas.html) by Vittorio Romeo

## Related links
* [Modern-Cpp::rvalue](../rvalue)
* [Modern-Cpp::universal delegate](../variadic/universal%20delegate) 
* [Modern-Cpp::tuple unpacking](../tuple/variadic_parameter_list) 
* [concept::requires](https://github.com/nikolaAV/skeleton/blob/master/algorithm/simple_xor/main.cpp) example of usage `__VA_ARGS__` macro with variadic parameters to express pceudo-keyword "requires".