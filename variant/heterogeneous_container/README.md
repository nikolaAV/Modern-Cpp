# Enumerating elements of different types in a heterogeneous container (C++17)
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

using shape                      = variant<circle,square,triangle>; 
using heterogeneous_container_t  = vector<shape>; 

int main()
{
   heterogeneous_container_t shapes {circle{}, square{}, triangle{} };

   // enumerate elements in the 'shapes' in OOP style (a la container of polymorphic types)
   for(auto s : shapes)
      visit([](auto s) {cout << s.draw() << endl;}, s );
```

# Related links
* [Original Article](https://habrahabr.ru/post/332084/) by JegernOUTT
* [std::visit](http://en.cppreference.com/w/cpp/utility/variant/visit) 
* [Unpacking & enumerating Tuples in C++14](https://github.com/nikolaAV/Modern-Cpp/tree/master/tuple/unpacking_tuples) by nikolaAV on GitHub

## Supported Compilers
* Microsoft (R) C/C++ Optimizing Compiler Version 19.10.xyz with option /std:c++latest ([Visual Studio 2017](https://www.visualstudio.com/vs/visual-studio-express/))