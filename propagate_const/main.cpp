#include <iostream>
#include <memory>
#include <string>
#include <experimental/propagate_const>
 
using namespace std;

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
        