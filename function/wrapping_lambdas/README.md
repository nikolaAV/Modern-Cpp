# Adding polymorphy by wrapping lambdas into std::function
It's natural that a STL container can't store completely different types if it has been  parametrized by the particular type. But however C++ allows the user to store any kind of function object, __only constraining to the call interface__, which takes a specific set of parameters. Example below illustrate how to solve this problem using `std::function`, which can act as a polymorphic wrapper around any lambda expression, __no matter if and what it captures__. 
```cpp
struct circle
{
   const char* draw() const { return "I'm a circle"; }
};

struct square
{
   const char* draw() const { return "I'm a square"; }
};

struct triangle
{
   const char* draw() const { return "I'm a triangle"; }
};

using shape                      = function<const char*(void)>; 
using heterogeneous_container_t  = vector<shape>; 

int main()
{
   heterogeneous_container_t v = {
       [c=circle{}]()     { return c.draw(); }
      ,[s=square{}]()     { return s.draw(); }
      ,[t=triangle{}]()   { return t.draw(); }
   };
   for(const auto& s:v)
      cout << s() << endl;
```

## Further informations
* [std::function](https://en.cppreference.com/w/cpp/utility/functional/function)
* [passing functions to functions](https://vittorioromeo.info/index/blog/passing_functions_to_functions.html) by Vittorio Romeo

## Related links
* [std::variant value type in a STL container](https://github.com/nikolaAV/Modern-Cpp/tree/master/variant/heterogeneous_container) by nikolaAV on GitHub
* [Lambda expressions](https://github.com/nikolaAV/Modern-Cpp/tree/master/lambda)

## Compilers
* [GCC 8.1.0](https://wandbox.org/)
* [clang 6.0.0](https://wandbox.org/)
* Microsoft (R) C/C++ Compiler 19.14 
