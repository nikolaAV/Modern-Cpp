# Computing with `constexpr`.
`constexpr` is a really powerful tool since it allows us to move computation to compile time rather than having to compute it at runtime. 
The advantage is that the same code can be used at both runtime and compile time. 
Of course, successfully evaluating a `constexpr` function still requires that all computational steps be possible and valid at compile time: Currently, that excludes things like heap allocation or throwing
exceptions. However, that does not mean we are not allowed to write these things in a `constexpr` function. We can do this, but we may not call it for compile time calculations in a way that would try to execute those lines. 
The standard actually demands, that if the evaluation of a `constexpr` function call makes the evaluation of “run time constructs” (this is not official standard wording) necessary, that function call is not a constant expression any more. 
The key thing is however that a `constexpr` function call remains a constant expression if no run time construct needs to be evaluated. 
Let’s for example build a little check against integer code of a symbol to be a hundred percent sure that symbol belongs to the [ASCII table](https://en.cppreference.com/w/cpp/language/ascii):
```cpp
constexpr unsigned char ascii_expects(int ch)
{ 
   return 0x00 <= ch && ch <= 0x7F? 
         static_cast<unsigned char>(ch)
      :  throw std::runtime_error{"no ASCII code"}
   ;
}
```
This check will always work, but in different ways. If we call the function with too large a value in a run time context, we will get the `std::runtime_error` thrown at run time. If we call it in a compile time context with such a large argument, the compiler will simply tell us that the function call is not a constant expression.
```cpp
constexpr auto copmile_ok   = ascii_expects(' ');    // Ok
constexpr auto copmile_err  = ascii_expects('\xAA'); // Compile Error: 'throw' is not a constant expression
int space = ' ';
int xAA   = '\xAA';
auto runtime_ok   = ascii_expects(space);    // Ok
auto runtime_err  = ascii_expects(xAA);      // Exception: "no ASCII code"
```

## Further informations
* [Modern C++ Features – constexpr](https://arne-mertz.de/2016/06/constexpr/) by Arne Mertz
* [P0595, The constexpr Operator](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2017/p0595r0.html) by Daveed Vandevoorde

## Related links
* [Other examples of compile time computing](../)

## Compilers
* [GCC 8.1.0](https://wandbox.org/)
* [clang 6.0.1](https://wandbox.org/)
* Microsoft (R) C/C++ Compiler 19.16 
