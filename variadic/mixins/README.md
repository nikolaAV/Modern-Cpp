# Mixin-based Type. How to introduce easily additional information without changing its interface.
Consider a simple 'Polygon' class that consists of a sequence of points:
```cpp
class Point
{
   double x_{0}, y_{0};
public:
   Point() = default;
   Point(double x, double y) : x_{x}, y_{y} {}
   // ...
};

class Polygon
{
   vector<Point> points_;   
public:
   // ...
```
This Polygon class would be more useful if the user could extend the set of information associated with each Point to include application-specific data such as
the color of each point, or perhaps associate a label with each point. One option to make this extension possible would be to parameterize Polygon based on the type of the point:
```cpp
template <typename P>
class Polygon
{
   vector<P> points_;   
public:
   // ...
```
Users could conceivably create their own Point-like data type that provided the same interface as Point but includes other application-specific data, using inheritance
```cpp
class LabeledPoint : public Point
{
    std::string label_;
public:
    LabeledPoint() : Point(), label_("") { }
    LabeledPoint(double x, double y) : Point(x, y), label_("") {
   // ...

class RgbPoint : public Point
{
    long rgb_;
public:
    RgbPoint() : Point(), Rgb_("") { }
    RgbPoint(double x, double y) : Point(x, y), Rgb_("") {
   // ...
```
This implementation has its shortcomings:
* It requires that the type Point be exposed to the user so that the user can derive from it
* The author of 'LabeledPoint' needs to be careful to provide exactly all of the same constructors as 'Point'
* This constraint becomes more problematic if 'Point' changes from one version of the 'Polygon' template to another: The addition of a new 'Point' constructor could require each derived class to be updated.  

_Mixins_ provide an alternative way to customize the behavior of a type without inheriting from it. Mixins essentially invert the normal direction of inheritance, because the new classes are “mixed in” to the inheritance hierarchy as base classes of a class template rather than being created as a new derived class. This approach allows the introduction of new data members and other operations without requiring any duplication of the interface. 
```cpp
template<typename... Mixins>
class Point : public Mixins...
{
   double x_{0}, y_{0};
public:
   Point() = default;
   Point(double x, double y) : x_{x}, y_{y} {}
   // ...
```
Now, we can “mix in” a base class containing a label to produce a 'LabeledPoint':
```cpp
class Label
{
   string label_;
public:
   // ...
};
using LabeledPoint = Point<Label>;
```
or even mix in several base classes:
```cpp
class Color
{
    long rgb_;
public:
   // ...
};
using AdvancedPoint = Point<Label,Color>;
```
Mixins are useful in cases where a template needs some small level of customization —such as decorating internally stored objects with user-specified data—without requiring the library to expose and document those internal data types and their interfaces.

## Further informations
* [C++ Templates - The Complete Guide, 2nd Edition](http://www.tmplbook.com/)by David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor, chapter 21.3
* [Mixin-Based Programming in C++](http://www.drdobbs.com/cpp/mixin-based-programming-in-c/184404445) 
## Related links
* [inheritance generation](../variadic/inheritance#template-parameter-pack-expansion-inheritance)
## Compilers
* [GCC 8.1.0](https://wandbox.org/)
* [clang 6.0.0](https://wandbox.org/)
* Visual C++ 19.14 
