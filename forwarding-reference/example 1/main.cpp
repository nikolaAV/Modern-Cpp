#include <string>
#include <iostream>
#include <sstream>

// http://habrahabr.ru/post/242639/

using namespace std;

struct A
{
    A(size_t n)  : n_(n)    { cout << "A::A("  << n_ << ")" << endl; }
    A(const A&a) : n_(a.n_) { cout << "A::A(const A& "<< n_ <<")" << endl; }
    A(A&& a)     : n_(a.n_) { cout << "A::A(A&& " << n_<< ")" << endl; }

    A& operator=(const A&) = delete;
    A& operator=(A&&) = delete;

    const string exec() const { return make_exec("A::exec() const",n_); }
    const string exec()       { return make_exec("A::exec()",n_); }

private:
    static string make_exec(const char* m, size_t n)
    {
        ostringstream ss;
        ss << m << ", " << n;
        return ss.str();
    }

private:
    size_t n_;
};

struct F1
{
    void operator()(A a) { cout << "f1(A a) -> " << a.exec() << endl;}
};

struct F2
{
    void operator()(A& a) { cout << "f2(A& a) -> " << a.exec() << endl;}
};

struct F3
{
    void operator()(const A& a) { cout << "f3(const A& a) -> " << a.exec() << endl;}
};

struct F4
{
    void operator()(A&& a) { cout << "f4(A&& a) -> " << a.exec() << endl;}
};

void test()
{
    cout << "*** call delegations. basic enumerations" << endl;
    F1 f1; F2 f2; F3 f3; F4 f4;
    A a{1};

    f1(a);
    f2(a);
    f3(a);
    //f4(a);  // <-- Correct: cannot bind A lvalue to A&&

    f1({2});
    //f2({3}); // <-- Correct: cannot bind A rvalue to A&
    f3({4});
    f4({5});
}



namespace c03
{

template <typename F, typename Arg>
void wrapper(F f, Arg arg)
{
    f(arg);
}

//template <typename F, typename Arg>
//void wrapper(F f, const Arg& arg)
//{
//    f(arg);
//}

void test()
{
    cout << "*** C++03 solution" << endl;

    F1 f1; F2 f2; F3 f3; 
	//F4 f4;
    A a{1};

    wrapper(f1,a);
    wrapper(f2,a);
    wrapper(f3,a);
    //wrapper(f4,a);  // <-- Correct: cannot bind A lvalue to A&&

    wrapper(f1,A{2});
    wrapper(f2,A{3});
    wrapper(f3,A{4});
    //wrapper(f4,A{5}); // <-- Correct: cannot bind A lvalue to A&&
}

}   // end of namespace c03


namespace c11
{



template <typename F, typename Arg>
void wrapper(F f, Arg&& arg)
{
    f(std::forward<Arg>(arg));
}


void test()
{
    cout << "*** C++11 solution" << endl;

    F1 f1; F2 f2; F3 f3; F4 f4;
    A a{1};

    wrapper(f1,a);
    wrapper(f2,a);
    wrapper(f3,a);
    //wrapper(f4,a);  // <-- Correct: cannot bind A lvalue to A&&

    wrapper(f1,A{2});
    //wrapper(f2,A{3}); // <-- Correct: cannot bind A rvalue to A&
    wrapper(f3,A{4});
    wrapper(f4,A{5});
}

}   // end of namespace c11



int main(int /*argc*/, char** /*argv[]*/)
{
    test();
    c03::test();
    c11::test();

    cout << "Press any key + <enter> to exit" << endl;
    cin.get();
    return 0;
}
