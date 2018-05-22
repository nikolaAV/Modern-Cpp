# Function concatenation with lambda expression
Let's suppose there are three free-standing functions: `f`, `g` and `h` and the user makes a function call like this: `f( g( h(...)))`;  Our purpose is to provide _the function call composition_ like it's done in functional programming language Haskell, `call = f | g | h; call(...);`
```cpp
   /**
      mathematical statement:
       ________
      v(x+y)*2     
   */

   auto sum    = [](auto x, auto y) { return x+y; };   
   auto twice  = [](auto x)         { return 2*x; };
   auto sqrt   = [](auto x)         { return std::sqrt(x); };

   auto formula = composite::start | sum | twice | sqrt;
   cout << formula(4,5) << endl;
   cout << formula(3.14,2.56) << endl;
```

## Further informations
* [Элементы функционального программирования в C++](https://habr.com/post/328624/) by Дмитрий Изволов

## Related links
* TBD

## Compilers
* [GCC 8.1.0](https://wandbox.org/)
* [clang 6.0.0](https://wandbox.org/)
* Microsoft (R) C/C++ Compiler 19.14 
