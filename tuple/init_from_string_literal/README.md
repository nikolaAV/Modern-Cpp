# Declaring Compile-Time std::tuple of characters initialized with pure C string literals
```cpp
constexpr auto t = make_tuple_chars("Hello, World!");
// t is an instance of tuple<char...> 
// {'H','e','l','l','o',',',' ','W','o','r','l','d','!'}
```

## Further informations
* TBD

## Related links
* [for_each(tuple&)](../for-each)
* [fold_expressions](../../variadic/fold_expressions)
* [variadic_indices](../../variadic/variadic_indices)

## Compilers
* [GCC 7.3.0](https://wandbox.org/)
* [clang 6.0.1](https://wandbox.org/)
* Microsoft (R) C/C++ Compiler 19.14 
