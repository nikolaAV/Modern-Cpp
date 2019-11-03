# IIFE for Complex Variable Initialization
The **IIFE** acronym stands for _“Immediately-invoked function expression”_.  
#### Motivation
What do you do when the code for a variable initialization is complicated? Do you move it to another method or write inside the current scope? 
```cpp
const auto myVar = /*some complex code here*/;
```
Using IIFE allows computing a value for a variable, even a const variable, with a compact notation.

#### Usage 1. Calling `()` at the end of the anonymous lambda.
```cpp
const auto myVar = [&] {
    return /*some complex code here*/;
}();
```

#### Usage 2. [`std::invoke()`](https://en.cppreference.com/w/cpp/utility/functional/invoke).
```cpp
const auto myVar = std::invoke([&] { 
    return /* some complex code here */; 
});
```

#### Usage 3. The named lambda and calling it later.
```cpp
auto initialiser = [&] { 
    return /* some complex code here */; 
};
const auto myVar = initialiser();
```

## Further informations
* [lambda as Immediately-Invoked Function Expression](https://articles.emptycrate.com/2014/12/16/complex_object_initialization_optimization_with_iife_in_c11.html) by Jason Turner
* [Complex initialization for a const variable](https://herbsutter.com/2013/04/05/complex-initialization-for-a-const-variable/) by Herb Sutter
* [C++ Tricks: IIFE for Complex Variable Initialization](https://www.bfilipek.com/2016/11/iife-for-complex-initialization.html) by Bartlomiej Filipek

## Related links

## Compilers
* [GCC 8.1.0](https://wandbox.org/)
* [clang 6.0.0](https://wandbox.org/)
* Microsoft (R) C/C++ Compiler 19.14 
