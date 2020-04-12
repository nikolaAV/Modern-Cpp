# Enumerating elements of different types in a heterogeneous container (C++17)
The code example below demonstrates how elements of different types can be stored in one container like it can be done in OOP using polymorphic types. 
```cpp
struct circle {
   const char* draw() const { return "I'm a circle"; }
};
struct square {
   const char* draw() const { return "I'm a square"; }
};
struct triangle {
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
And one more point. Let's suppose our shapes to be drawn use different methods like this:
```cpp
struct circle {
   const char* draw() const { return "I'm a circle"; }
};
struct square {
   const char* sketch() const { return "I'm a square"; }
};
struct triangle {
   const char* paint() const { return "I'm a triangle"; }
};
```
then applying ["The overload lambda Pattern"](https://www.bfilipek.com/2019/02/2lines3featuresoverload.html) we may draw every shape stored in the  heterogeneous container. 
```cpp
   const auto composite_visitor = overloaded {
       [](const circle& c)   { cout << c.draw() << endl; }
      ,[](const square& s)   { cout << s.sketch() << endl; }
      ,[](const triangle& t) { cout << t.paint() << endl; }
   };
   for(auto s : shapes)
      visit(composite_visitor, s );
```

## Further informations
* [Original Article](https://habrahabr.ru/post/332084/) by JegernOUTT
* [std::visit](http://en.cppreference.com/w/cpp/utility/variant/visit)
* [Pattern for visitation of `std::variant`](https://www.bfilipek.com/2019/02/2lines3featuresoverload.html)
* [Runtime Polymorphism with `std::variant` and `std::visit`](https://www.bfilipek.com/2020/04/variant-virtual-polymorphism.html) by Bartlomiej Filipek

## Related links
* [Unpacking & enumerating Tuples in C++14](../../tuple/unpacking_tuples) by nikolaAV on GitHub
* [Wrapping lambdas into std::function](../../function/wrapping_lambdas) 
* [Lambda. The overload Pattern](../../lambda/lambda_overloaded)

## Supported Compilers
* Microsoft (R) C/C++ Optimizing Compiler Version 19.16.xyz with option /std:c++latest
* GCC 8.1.0
* Clang 7.0.0

