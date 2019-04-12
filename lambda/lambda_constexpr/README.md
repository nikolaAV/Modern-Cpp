# `constexpr` Lambda Expressions
Since C++17, if possible, the standard defines operator() for the lambda type __implicitly__ as `constexpr`  
From [expr.prim.lambda #4](https://timsong-cpp.github.io/cppwp/n4659/expr.prim.lambda#closure-4):  
> The function call operator is a constexpr function if either the corresponding lambda-expression’s parameter-declaration-clause is followed by constexpr, or it satisfies the requirements for a constexpr function.  

Example:
```cpp
template<typename Range, typename Func, typename T>
constexpr T accumulate(const Range& range, Func func, T init) {
   for(auto&& elem:range)
      init += func(elem);
   return init; 
}

int main()
{
   constexpr std::array arr{1,2,3,4,5};
   static_assert(1+4+9+16+25==accumulate(  arr
                                          ,[](auto x){ return x*x; }
                                          ,0)
   );
}
```

## Further informations
* [constexpr Lambda Expressions](https://www.bfilipek.com/2019/03/lambdas-story-part2.html)

## Related links
* [Other examples of compile time computing](../../constexpr)
* [Back to lambda section](../)

## Compilers
* [GCC 8.1.0](https://wandbox.org/)
* [clang 7.0.0](https://wandbox.org/)
* Microsoft (R) C/C++ Compiler 19.14 
