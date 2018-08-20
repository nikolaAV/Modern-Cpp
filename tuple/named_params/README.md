# Named parameters for functions in C++14.  
Let's suppose we have a function with ill-formed signature which comes from a third-party library.
```cpp
    void draw_rectangle(
         const std::string& title
        ,int left=0, int top=0
        ,int width=10, int height=20
        ,bool fill = false
    );
```
In C++, functions have positional arguments. This means, for functions with many parameters, the programmer has to remember __the types__ and __the order__ in which to pass them. Furthermore, default values can only be given to the last parameters, so it is not possible to specify one of the later parameters and use the default value for former ones.  
Named parameters might help. Here is one of the possible implementations:
#### Step 1. Every parameter must be represented a separate type.
```cpp
   struct title   { std::string value; };
   struct left    { int value; };
   struct top     { int value; };
   struct width   { int value; };
   struct height  { int value; };
   struct fill    { bool value; };
```
#### Step 2. Make a wrapper of 'draw_rectangle' accepting parameters as variadic template.
```cpp
    template <typename... Ts>
    void draw_rectangle(Ts... ts)
    {
       const auto t = std::make_tuple(ts...);
       draw_rectangle(  // <-- delegates call to the original
           nparam::get<title>(t)
          ,nparam::get<left>(t,0),nparam::get<top>(t,0)
          ,nparam::get<width>(t,10),nparam::get<height>(t,20)
          ,nparam::get<fill>(t,false)
       );
    }
```
#### Step 3. Invocation itself. 
```cpp
    draw_rectangle(title{"test"},fill{true},height{100});
    draw_rectangle(fill{true});
    // ...
```
Parameter-types defined as structures are passed as anonymous objects, which are constructed via aggregate initialization, to a variadic template function, which forwards these function arguments (or the default values) in the correct order to the actual implementation by the third-party function with a fixed number of positional arguments.

## Further informations
* [Bring named parameters in modern C++](https://isocpp.org/blog/2014/12/named-parameters-in-modern-cpp)
* [Proposal #4172](http://www.open-std.org/JTC1/SC22/WG21/docs/papers/2014/n4172.htm)
* [Revisiting the named parameter idiom in C++14](https://www.numbercrunch.de/blog/2015/11/revisiting-the-named-parameter-idiom-in-c14/)
* [Strong types for strong interfaces](https://www.fluentcpp.com/2016/12/08/strong-types-for-strong-interfaces/)
## Related links
* [Check type existence in the tuple](./type_existence)
## Compilers
* [GCC 8.1.0](https://wandbox.org/)
* [clang 6.0.0](https://wandbox.org/)
* Visual C++ 19.14 
