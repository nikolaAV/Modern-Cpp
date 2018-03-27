# propagate_const ([C++ library fundamentals TS v2](http://en.cppreference.com/w/cpp/experimental/lib_extensions_2))

Inside `const` methods all member pointers become constant __pointers__.
From practical point of view, there is a sence to make data-members (which are pointed by these pointers) constant also, i.e. to provide a real __logic constness__.

```cpp
#include <experimental/propagate_const>

template <typename T>
using unique_pcptr = experimental::propagate_const<unique_ptr<T>>;

struct widget
{
   string foo() const   { return "widget::foo(const)"; }
   string foo()         { return "widget::foo(non-const)"; }
};
 
class bar
{
   unique_ptr<widget>   member1_ {make_unique<widget>()};
   unique_pcptr<widget> member2_ {make_unique<widget>()};
public:
   void foo() const  { 
      cout << "unique_ptr: " << member1_->foo() << endl
           << "propagate_const_ptr: " << member2_->foo() << endl;
   }
};
 
int main()
{
   const bar b;
   b.foo();
}
```
Output
```cpp
unique_ptr: widget::foo(non-const)
propagate_const_ptr: widget::foo(const)
```

## Further informations
* [How to propagate const on a pointer data member?](http://www.bfilipek.com/2018/01/propagate-const.html) by Bartlomiej Filipek
* [std::experimental::propagate_const](http://en.cppreference.com/w/cpp/experimental/propagate_const)

## Related links
* [Function overloading. const-object & const-function](https://github.com/nikolaAV/Storehouse-Of-Knowledge/blob/master/list_of_questions.md#function-overloading-const-object--const-function)

## Compilers
* [GCC 7.2.0](https://wandbox.org/)
* [clang 5.0.0](https://wandbox.org/)
 