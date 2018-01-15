# Overloaded Lambdas
An easy way to compose a lambda with multiple overloaded function call syntax. 

```cpp
    // The construct
    auto functor = lambda::overloaded {
         [](bool v) { ... }
        ,[](int v)  { ... }
        ,[](const std::string& v)  { ... }
        ,[](widget v)  { ... }
    };
    // is an equivalent of
    struct Functor
    {
        ... operator()(bool v) { ... }
        ... operator()(int v)  { ... }
        ... operator()(const std::string& v) { ... }
        ... operator()(widget v) { ... }
    };
    Functor functor{...}; 

    // which is aimed to be used on client side like
    functor(true);      // operator()(bool) 
    functor(23);        // operator()(int) 
    functor("hello");   // operator()(const std::string&) 
    functor(widget{});  
```

## Further informations
* [Overloading Lambdas in C++17](https://dev.to/tmr232/that-overloaded-trick-overloading-lambdas-in-c17) by Tamir Bahar
* [Overloaded Lambdas](http://cpptruths.blogspot.com/2014/05/fun-with-lambdas-c14-style-part-2.html) by Sumant Tambe
* [Heterogeneous container (C++17)](https://habrahabr.ru/post/332084/) by JegernOUTT

## Related links
* [nikolaAV\::modern-cpp::heterogeneous-container](https://github.com/nikolaAV/Modern-Cpp/tree/master/variant/heterogeneous_container)
* [nikolaAV\::modern-cpp\::fold-expressions::inheritance](https://github.com/nikolaAV/Modern-Cpp/tree/master/variadic/inheritance)

