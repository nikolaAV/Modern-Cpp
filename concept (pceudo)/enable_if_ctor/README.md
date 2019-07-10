# Partially disabling member function templates when they might hide copy or move constructors
### Symptoms
Consider the following example:
```cpp
   class Person {
      string name_;
   public:
      explicit Person(const string& n) : name_(n) {
         cout << "ctor(copy, 1 param)" << endl;
      }
      explicit Person(string&& n) : name_(move(n)) {
         cout << "ctor(move, 1 param)" << endl;
      }
      Person(const Person& p) : name_(p.name_) {
         cout << "ctor(copy, Person)" << endl;
      }
      Person(Person&& p) : name_(move(p.name_)) {
         cout << "ctor(move, Person)" << endl;
      }
   };

int main()
{
   string s = "name";

   Person p1(s);            // ctor(copy, 1 param), Line A
   Person p2("other name"); // ctor(move, 1 param), Line B
   Person p3(p1);           // ctor(copy, Person),  Line C
   Person p4(move(p1));     // ctor(move, Person),  Line D
}
```
Here, we have a class Person with a string member __name___ for which we provide initializing constructors. 
To support move semantics, we overload the constructor taking a `std::string`.
```cpp
// a version for string object the caller still needs, for which name is initialized by a copy of the passed argument
Person(const string& n);

// a version for movable string object, for which we call std::move() to “steal” the value from
Person(string&& n);
```
As expected, the first is called for passed string objects that are in use (`lvalues`, _Line A_), while the latter is called for movable objects (`rvalues`, _Line B_).  
Besides these constructors, the example has specific implementations for the _copy_ and _move_ constructor to see when a __Person__ as a whole is copied/moved (_Line C_,_Line D_).  

Now let’s replace the two string constructors with one generic constructor perfect forwarding the passed argument to the member name:
```cpp
   class Person {
      string name_;
   public:
      template <typename STR>
      explicit Person(STR&& n) : name_(forward<STR>(n)) {
         cout << "ctor(template, 1 param)" << endl;
      }
      ...
```
and examine again the mentioned client code above. 
Construction with passed string works fine, as expected:
```cpp
   string s = "name";

   Person p1(s);            // ctor(copy, 1 param), Line A
   Person p2("other name"); // ctor(move, 1 param), Line B
```
Note how the construction of p2 does not create a temporary string in this case: 
The parameter STR is deduced to be of type `char const[11]`. 
Applying `std::forward<STR>` to the pointer parameter of the constructor has not much of an effect, and the __name___ member is thus constructed from a null-terminated string.  
But when we attempt to call the copy constructor, we get an error:
```cpp
   Person p3(p1);           // Compile Error
```
while initializing a new __Person__ by a movable object still works fine:
```cpp
   Person p4(move(p1));     // ctor(move, Person),  Line D
```
The problem is that, according to the [overload resolution rules of C++](https://github.com/nikolaAV/Storehouse-Of-Knowledge/blob/master/questions/README.md#special-member-function-generation-constructor-template-part-2) for a nonconstant lvalue Person 'p1' the member `template Person(STR&&)` is a better match than the (usually predefined) copy constructor `Person(const Person&)`. 
STR is just substituted with Person&, while for the copy constructor a conversion to `const` is necessary.  
You might think about solving this by also providing a nonconstant copy constructor:
```cpp
   Person(Person&); 
```
However, that is only a partial solution because for objects of a derived class, the member template is still a better match. 
What you really want is to disable the member template for the case that the passed argument is a Person or an expression that can be converted to a Person. 
This can be done by using [`std::enable_if<>`](https://en.cppreference.com/w/cpp/types/enable_if).

### Disable Templates with enable_if<>
Since `C++11`, the C++ standard library provides a helper template `std::enable_if<>` to ignore function templates under certain compile-time conditions. 
For example, if a function template foo<>() is defined as follows:
```cpp
template<typename T>
typename std::enable_if_t<CONDITION> foo() {...}
```
this definition of foo<>() is ignored if CONDITION yields `false`. 
If CONDITION yields `true`, the function template instance expands to void foo(){...}.  
Back to our problem with the constructor template, we have to solve is to disable its declaration if the passed argument STR has the right type (i.e., is a `std::string` or a type convertible to `std::string`).
For this, we use another standard type trait, [`std::is_convertible<FROM,TO>`](https://en.cppreference.com/w/cpp/types/is_convertible). 
With C++17, the corresponding declaration looks as follows:
```cpp
      template <typename STR, typename = enable_if_t<is_convertible_v<STR,string>>>
      explicit Person(STR&& n) : name_(forward<STR>(n)) {
         cout << "ctor(template, 1 param)" << endl;
      }
```
If type STR is convertible to type `std::string`, the whole declaration expands to
```cpp
      template <typename STR, typename = void>
      explicit Person(STR&& n) : name_(forward<STR>(n)) {
         cout << "ctor(template, 1 param)" << endl;
      }
```
If type STR is not convertible to type std::string, the whole function template is ignored.

## Further informations
* [C++: enable_if](http://codeofthedamned.com/index.php/enable_if) on Embedded Alchemy. 
* [C++ Templates - The Complete Guide, 2nd Edition](http://www.tmplbook.com/) by David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. 6.3 Disable Templates with enable_if<>, page 150 
## Related links
* [enable_if](../enable_if)
* [simple_xor](https://github.com/nikolaAV/skeleton/tree/master/algorithm/simple_xor), the impressive set of overloads
* [issue when a template constructor is better match in the overload resolution than a copy constructor](https://github.com/nikolaAV/Storehouse-Of-Knowledge/blob/master/questions/README.md#special-member-function-generation-constructor-template-part-2)
## Compilers
* [GCC 8.1.0](https://wandbox.org/)
* [clang 6.0.0](https://wandbox.org/)
* Visual C++ 19.14 
