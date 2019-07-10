#include <iostream>
#include <string>
#include <string_view>
#include <utility>
#include <type_traits>

/**
   The unpleasant effect which can be occured accidentally and causes surprising behaviour 
   when member function template is defined that accepts the same parameter as copy or move constructors.
   class C {
      C(const C&);
      template <typename T> C(T&&);
   };
   For the code below
   C c1;
   C c2{c1}; // <--- !!!
   the member function template is a better match (!!!) for copying a C than the copy constructor.

   /see https://github.com/nikolaAV/Storehouse-Of-Knowledge/blob/master/questions/README.md#special-member-function-generation-constructor-template-part-2
*/

using namespace std;

namespace v1
{

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

} // namespace v1


namespace v2
{
   /**
      Attempt 1
      Now let’s replace the two string constructors with one generic constructor perfect
      forwarding the passed argument to the member name

      There is an unpleasant issue here,
      template ctor is more preferable to be called insted of ctor(copy) !!!
      \see https://github.com/nikolaAV/Storehouse-Of-Knowledge/blob/master/questions/README.md#special-member-function-generation-constructor-template-part-2
   */
   class Person {
      string name_;
   public:
      template <typename STR>
      explicit Person(STR&& n) : name_(forward<STR>(n)) {
         cout << "ctor(template, 1 param)" << endl;
      }
      Person(const Person& p) : name_(p.name_) {
         cout << "ctor(copy, Person)" << endl;
      }
      Person(Person&& p) : name_(move(p.name_)) {
         cout << "ctor(move, Person)" << endl;
      }
   };

} // namespace v2

namespace v3
{
   /**
      Attempt 2
      Partially disabling template constructor with enable_if<> for case if parameter STR is exactly Person.   

      \see  http://www.tmplbook.com/, 
            C++ Templates - The Complete Guide, 2nd Edition by David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor
            6.3 Disable Templates with enable_if<>, page 150
   */
   class Person {
      string name_;
   public:
      template <typename STR, typename = enable_if_t<is_convertible_v<STR,string>>>
      explicit Person(STR&& n) : name_(forward<STR>(n)) {
         cout << "ctor(template, 1 param)" << endl;
      }
      Person(const Person& p) : name_(p.name_) {
         cout << "ctor(copy, Person)" << endl;
      }
      Person(Person&& p) : name_(move(p.name_)) {
         cout << "ctor(move, Person)" << endl;
      }
   };

} // namespace v3

namespace v4
{
   /**
      Attempt 3
      Now let’s replace the two string constructors with one 'string_view'
      passed argument to the member name
      No overhead for the temporary 'std::string' creation 
      in case if an input argument is the literal constant (rvalue) is required

      \see Effective Modern C++ by Scott Meyers
           Item 41: Consider pass by value for copyable parameters that are cheap to move and always copied.
           page 281
   */
   class Person {
      string name_;
   public:
      explicit Person(string_view n) : name_(n) {
         cout << "ctor(string_view, 1 param)" << endl;
      }
      Person(const Person& p) : name_(p.name_) {
         cout << "ctor(copy, Person)" << endl;
      }
      Person(Person&& p) : name_(move(p.name_)) {
         cout << "ctor(move, Person)" << endl;
      }
   };

} // namespace v4



int main()
{
   string s = "name";

   v1::Person p11(s);            // ctor(copy, 1 param)
   v1::Person p12("other name"); // ctor(move, 1 param)
   v1::Person p13(p11);          // ctor(copy, Person)
   v1::Person p14(move(p13));    // ctor(move, Person)

   v2::Person p21(s);            // ctor(template, 1 param)
   v2::Person p22("other name"); // ctor(template, 1 param)
//   v2::Person p23(p21);          // Compile error: attempt to call ctor(template, 1 param)
   v2::Person p24(move(p22));    // ctor(move, Person)

   v3::Person p31(s);            // ctor(template, 1 param)
   v3::Person p32("other name"); // ctor(template, 1 param)
   v3::Person p33(p31);          // ctor(copy, Person)
   v3::Person p34(move(p32));    // ctor(move, Person)

   v4::Person p41(s);            // ctor(string_view, 1 param)
   v4::Person p42("other name"); // ctor(string_view, 1 param)
   v4::Person p43(p41);          // ctor(copy, Person)
   v4::Person p44(move(p42));    // ctor(move, Person)
}
