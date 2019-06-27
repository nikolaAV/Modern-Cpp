# Multiple dispatch in C++17 with `std::variant` and `std::visit`
In C++/OOP terms, multi-dispatch is the ability to choose which version of a function to call based on [dynamic types](https://en.cppreference.com/w/cpp/language/type#Dynamic_type) of the parameters of [static types](https://en.cppreference.com/w/cpp/language/type#Static_type) passed to the function call. 
Or the other words, the function accepting parameters of [polymorphic type](https://en.cppreference.com/w/cpp/language/object#Polymorphic_objects) should initiate a call according to real types hidden by the interface.  
If we take the classic example of [the Shape Inheritance](http://python.cs.southern.edu/csharpbook/html/ch12s08.html) we would like the function __intersect__ defined as 
```cpp
void intersect(const shape& left, const shape& right) {
    // ...
}
```
to do work for real objects passed into it.  
```cpp
intersect(rectangle{...}, circle{...});
// an expected result is drawing of the intersection between 'rectangle' object and 'circle' object.
```
Applying OOP style, if the calling function depends on the only argument, then it can be implemented as an overriden _virtual_ function-member for each inherited type and invoked like this:
```cpp
class shape {
   virtual draw() const = 0; 
};
class rectangle {
   draw() override {...} 
};
...
void draw(const shape& s) {
   s.draw();   // single dispatch, 
}
```
If the calling function depends on the two arguments, then we can implement it by using 
* dynamic_cast to get [RTTI](https://en.cppreference.com/w/cpp/types/type_info) ability
* well-known [_double dispatch_](https://gieseanw.wordpress.com/2018/12/29/stop-reimplementing-the-virtual-table-and-start-using-double-dispatch/) mechanism.
   
The problem is getting obvious when the number of input arguments gets quite value. A solution based on polymorphic type cannot be acceptable because OOP style does not support multi-methods directly.  
Is there alternative?  
Let's try to consider an approach called [static polymorphism](https://beginnersbook.com/2013/04/runtime-compile-time-polymorphism/) which can be implemented by means [`std::variant`](https://en.cppreference.com/w/cpp/utility/variant) and [`std::visit`](https://en.cppreference.com/w/cpp/utility/variant/visit).  
So we have related types like _the Shape Inheritance_ mentioned above but the inheritance is no longer required. 
```cpp
class circle     {...};
class square     {...};
class triangle   {...};
```
The total number of possible combinations which can be intersected is 9.
```cpp
void intersect(const circle&, const circle&);
void intersect(const circle&, const square&);
void intersect(const circle&, const triangle&);
void intersect(const square&, const square&);
void intersect(const square&, const circle&);
void intersect(const square&, const triangle&);
void intersect(const triangle&, const triangle&);
void intersect(const triangle&, const circle&);
void intersect(const triangle&, const square&);
```
Next step is to introduce an analog of the interface which all these terminal classes implement to.
```cpp
using shape  = std::variant<circle,square,triangle>;
```
Then we are able to write polymorphic function accepting two parameters of shape type.
```cpp
void intersect(const shape& left, const shape& right) {
   std::visit(
      [](auto const& s1, auto const& s2) { intersect(s1,s2); }
      ,left,right
   );
}
```
and test it
```cpp
shape factory(size_t id) {
   switch(id) {
      case 1 : return square{};
      case 2 : return triangle{};
   }
   return circle{};
}

const auto s0 = factory(0);
const auto s1 = factory(1);
const auto s2 = factory(2);

intersect(s0,s1);
intersect(s1,s2);
intersect(s2,s0);
```
That is all.   

## Further informations
* [A polyglot's guide to multiple dispatch](https://eli.thegreenplace.net/2016/a-polyglots-guide-to-multiple-dispatch/) by Eli Bendersky
* [Double dispatch and Visitor pattern](https://gieseanw.wordpress.com/2018/12/29/stop-reimplementing-the-virtual-table-and-start-using-double-dispatch/)
* [How To Use std::visit With Multiple Variants](https://www.bfilipek.com/2018/09/visit-variants.html) by Bartlomiej Filipek 
* [Open Multi-Methods for C++](http://www.stroustrup.com/multimethods.pdf) by Peter Pirkelbauer, Yuriy Solodkyy, Bjarne Stroustrup

## Related links
* [Heterogeneous container](../heterogeneous_container) 
* [back to 'variant' section](../)

## Supported Compilers
* Microsoft (R) C/C++ Optimizing Compiler Version 19.16.xyz with option /std:c++latest
* GCC 8.1.0
* Clang 7.0.0

