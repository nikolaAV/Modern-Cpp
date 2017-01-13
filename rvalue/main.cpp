#include <string>
#include <iostream>

using namespace std;

namespace
{

const char* readable(...)          { return "Ellipsis"; }
const char* readable(int&)         { return "l-value"; }
const char* readable(const int&)   { return "const l-value"; }
const char* readable(int&&)        { return "r-value"; }
const char* readable(const int&&)  { return "const r-value"; }

int&& xvalue()  { return 5; }
int   prvalue() { return 5; }
int&  lvalue()  { static int i{10}; return i; }

}

void test_expression_types()
{
    cout << "test_expression_types" << endl;

    int a{0}, b{1};
    const int&& r_ref = 99;
    cout << "int a; -> " << readable(a) << endl;
    cout << "literal '33'; -> " << readable(33) << endl;
    cout << "expression (a+b); -> " << readable(a+b) << endl;
    cout << "int&& xvalue(); -> " << readable(xvalue()) << endl;
    cout << "int   prvalue(); -> " << readable(prvalue()) << endl;
    cout << "int&  lvalue(); -> " << readable(lvalue()) << endl;
    cout << "const int&& r_ref; -> " << readable(r_ref) << endl;
}

void test_reference()
{
    cout << "test_reference" << endl;

    {
        int a{0};
        int& lvalue = a;
        const int& lvalue_const = a;
        // int&& rvalue = a; ERROR
        // const int&& rvalue_const = a; ERROR
        int&& rvalue = std::move(a);
    }
    {
        // int& lvalue = 9; ERROR
        const int& lvalue_const = 9;
        int&& rvalue = 9;
        const int&& rvalue_const = 9;
    }
    {
        int& lvalue = ::lvalue();
        const int& lvalue_const = ::lvalue();
    //    int&& rvalue = ::lvalue();
    //    const int&& rvalue_const = ::lvalue();
    }
    {
    //    int& lvalue = ::prvalue();
        const int& lvalue_const = ::prvalue();
        int&& rvalue = ::prvalue();
        const int&& rvalue_const = ::prvalue();
    }

}

int main(int /*argc*/, char** /*argv[]*/)
{
    test_expression_types();
    test_reference();


    cout << "Press any key + <enter> to exit" << endl;
    cin.get();
    return 0;
}
