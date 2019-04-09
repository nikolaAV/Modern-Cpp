#include <iostream>

using std::cin;
using std::cout;
using std::endl;

// std::thread member emulation
// because Cygwin GCC 4.7.2 under Windows doesn't support them
//

struct mutex
{
    void lock()     { cout << "mutex::lock" << endl; }
    void unlock()   { cout << "mutex::unlock" << endl; }
};

struct lock_guard
{
    explicit lock_guard(mutex& m) : m_(m)
    {
        m_.lock();
    }
    ~lock_guard()
    {
        m_.unlock();
    }

    lock_guard() = delete;
    lock_guard(const lock_guard&) = delete;
    lock_guard& operator=(const lock_guard&) = delete;
    lock_guard(lock_guard&&) = delete;
    lock_guard& operator=(lock_guard&&) = delete;

private:
    mutex&  m_;
};

//
// Original idea: http://herbsutter.com/elements-of-modern-c-style/
//

template <typename T, typename F>
void lock(T& t, F f)
{
    lock_guard hold{t};
    f();
}

// Usage:
// mutex mtx;
// ...
// lock( mtx, [&]{
//    ...
//    ...
// });


struct A
{
    A& operator=(size_t v)  { x_=v; return *this; }
    A& operator++()         { x_++; return *this; }
    A& operator--()         { x_--; return *this; }
    operator size_t() const { return x_; }

private:
    size_t x_ = 0;
};

A a;
mutex mtx;

static void test1()
{
    cout << "*** test1: RAII style" << endl;

    {   // Block begin
        lock_guard hold(mtx);
        a = 10;
        ++a; ++a; ++a; ++a;
        cout << "a1=" << a << endl;
    }   // Block end
    --a;
    cout << "a2=" << a << endl;
}

static void test2()
{
    cout << "*** test2: C++11 with lambda style" << endl;

    lock(mtx, [&] { // Block begin
        a = 20;
        ++a; ++a; ++a; ++a;
        cout << "a1=" << a << endl;
    });             // Block end
    --a;
    cout << "a2=" << a << endl;
}


int main(int /*argc*/, char** /*argv[]*/)
{
    test1();
    test2();

    cout << "Press any key + <enter> to exit" << endl;
    cin.get();
    return 0;
}
