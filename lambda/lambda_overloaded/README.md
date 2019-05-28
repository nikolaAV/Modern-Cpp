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
* [2 Lines Of Code and 3 C++17 Features - The overload Pattern](https://www.bfilipek.com/2019/02/2lines3featuresoverload.html) by Bartlomiej Filipek
* [The double functor trick](https://www.fluentcpp.com/2017/03/09/functors-are-not-dead-the-double-functor-trick/) by Jonathan Boccara

## Related links
* [nikolaAV\::modern-cpp::heterogeneous-container](https://github.com/nikolaAV/Modern-Cpp/tree/master/variant/heterogeneous_container)
* [nikolaAV\::modern-cpp\::fold-expressions::inheritance](https://github.com/nikolaAV/Modern-Cpp/tree/master/variadic/inheritance)

