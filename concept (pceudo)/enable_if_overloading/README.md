# Overload resolution for template function with conditional removement by means std::enable_if<>.  
Let's suppose we need to write template function with one parametrized parameteter like this:
```cpp
template <typename T>
T foo(T value) {
    // common case
}
```
For one reason or another you are required to provide specific implementation for _integral_ type.
```cpp
foo(int);           // special case
foo(double);        // common case
foo(const char*);   // common case
```

Of course, it can be done by introducing a free-standing function
```cpp
int foo(int value) {
    // special case
}
```
The given example is far away from a reality but in a practice sometimes we  need to use overloaded template functions. i.e. there are some cases when using free-standing functions are not quite acceptable.   
Going back to our example in order to satisfy the requirement (a special case for all _integral_ types) we must provide provide a bundle of overloaded functions: foo(`long`), foo(`char`), foo(`unsigned`), etc.
It's an annoying and error-prove routine.  
Well, the first attempt will not work
```cpp
template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
T foo(T v) {
    // special case
}

template <typename T, typename = std::enable_if_t<!std::is_integral_v<T>>>
T foo(T v) {
    // common case
}
```
The compiler says: "function template 'foo' has already been defined".
It may not instantiate every function, however, it does catalog every definition. Even though there is a definition for a false case that should not result in the instantiation of that version, __it does not affect the overload resolution of the functions__.  `std::enable_if` definition needs to contain a type that is dependent on the expression.  
There are three ways how it can be done correctly:

#### Function returns `std::enable_if<>::type`
```cpp
   template <typename T>
   std::enable_if_t<std::is_integral_v<T>,T>
   foo(T v) {
        // special case
   }

   template <typename T>
   std::enable_if_t<!std::is_integral_v<T>,T>
   foo(T v) {
      // common case
   }
```
#### Function accepts a default parameter of type that deduced by `std::enable_if<>::type`. 
```cpp
   template <typename T>
   T foo(T v, std::enable_if_t<std::is_integral_v<T>,T>* = nullptr) {
      // specific case
   }
   
   template <typename T>
   T foo(T v, std::enable_if_t<!std::is_integral_v<T>,T>* = nullptr) {
      // common case
   }
```
#### Function defined with default anonymous (unnamed) template parameter. 
```cpp
   template <typename T, std::enable_if_t<std::is_integral_v<T>,T>* = nullptr>
   T foo(T v) {
      // specific case
   }
   
   template <typename T, std::enable_if_t<!std::is_integral_v<T>,T>* = nullptr>
   T foo(T v) {
     // common case
   }
```
Note, while the same amount of code is required in this form, the declaration is moved from the function parameter (see the previous) list to the template parameter list. The template parameter is not a type, it's a value (`nullprt`) of pointer to type deduced by `std::enable_if`.


## Further informations
* [C++: enable_if](http://codeofthedamned.com/index.php/enable_if) on Embedded Alchemy. 
## Related links
* TBD
## Compilers
* [GCC 8.1.0](https://wandbox.org/)
* [clang 6.0.0](https://wandbox.org/)
* Visual C++ 19.14 
