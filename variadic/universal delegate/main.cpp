#include <string>
#include <iostream>
#include <vector>
#include <type_traits>
#include <utility>
#include <algorithm>
#include <numeric>

using namespace std;


template <typename Function, typename... Args>
inline 
typename std::result_of<Function(Args...)>::type
call(Function&& f, Args... args)
{
    // prologue, std::lock_guard<std::mutex> lock(g_i_mutex); as example 
    return f(std::forward<Args>(args)...);
    // epilogue
}

/**
    user defined type & functions
    just to test
*/
struct record
{
};

inline
record operator+(const record& l, const record& )
{
    return l;
}

void    foo1()              {}
void    foo2(const record&) {}
record  foo3()              { return {}; }
template <typename T> 
inline
T foo4(const T& t)          { return t; }


/**
    Signature: void (const Type &a);    
*/
    // f1 - pure function
    void f1_1(const record&) {};

    // f2 - functor
    struct XYZ { void operator()(const record&) {} } f1_2;

    // f3 - lambda
    auto f1_3 = [](const record&) {};

/**
    Signature: Type(const Type &a);
*/
    // f1 - pure function
    record f2_1(const record& r) { return r; };

    // f2 - functor
    struct XYZ2 { record operator()(const record& r) { return r;} } f2_2;

    // f3 - lambda
    auto f2_3 = [](const record& r) { return r; };


/**
    Signature: Type(const Type1 &a, const Type2 &b);
*/
    // f1 - pure function
    record f3_1(const record& r, const record&) { return r; };

    // f2 - functor
    struct XYZ3 { record operator()(const record& r, const record&) { return r;} } f3_2;

    // f3 - lambda
    auto f3_3 = [](const record& r, const record&) { return r; };


template <typename F>
void my_for_each(record* begin, record* end, F f)
{
    for(;begin != end;++begin)
        f(*begin);
}

template <typename F>
void my_transform(record* begin, record* end, record* out,F f)
{
    for(;begin != end;++begin,++out)
        *out = f(*begin);
}

template <typename F>
record my_accumulate(record* begin, record* end, record init, F f)
{
    for(;begin != end;++begin)
        init = f(init,*begin);
    return init;
}

int main(int , char*[])
{
   record r;
   vector<record> v;
   vector<record> out;

   call(foo1);
   call(foo2,record{});
   r = call(foo3);
   r = call(foo4<record>, record{});

   std::cout << std::boolalpha;
   std::cout << std::is_function<decltype(f1_1)>::value << '\n';
   std::cout << std::is_function<decltype(f1_2)>::value << '\n';
   std::cout << std::is_function<decltype(f1_3)>::value << '\n';

   for_each(begin(v),end(v), f1_1 );
   for_each(begin(v),end(v), f1_2 );
   for_each(begin(v),end(v), f1_3 );
   call(for_each<decltype(begin(v)),decltype(&f1_1)>,begin(v),end(v),f1_1);
   call(for_each<decltype(begin(v)),decltype(f1_2)>,begin(v),end(v),f1_2);
   call(for_each<decltype(begin(v)),decltype(f1_3)>,begin(v),end(v),f1_3);
   my_for_each(&v[0],&v[1], f1_1 );
   my_for_each(&v[0],&v[1], f1_2 );
   my_for_each(&v[0],&v[1], f1_3 );
   call(my_for_each<decltype(f1_1)>,&v[0],&v[1],f1_1);
   call(my_for_each<decltype(f1_2)>,&v[0],&v[1],f1_2);
   call(my_for_each<decltype(f1_3)>,&v[0],&v[1],f1_3);

   transform(begin(v),end(v), begin(out), f2_1 );
   transform(begin(v),end(v), begin(out), f2_2 );
   transform(begin(v),end(v), begin(out), f2_3 );
   call(transform<decltype(begin(v)),decltype(begin(out)),decltype(&f2_1)>,begin(v),end(v), begin(out), f2_1);
   call(transform<decltype(begin(v)),decltype(begin(out)),decltype(f2_2)>,begin(v),end(v), begin(out), f2_2);
   call(transform<decltype(begin(v)),decltype(begin(out)),decltype(f2_3)>,begin(v),end(v), begin(out), f2_3);
   my_transform(&v[0],&v[1],&out[0],f2_1 );
   my_transform(&v[0],&v[1],&out[0],f2_2 );
   my_transform(&v[0],&v[1],&out[0],f2_3 );
   call(my_transform<decltype(f2_1)>,&v[0],&v[1],&out[0],f2_1);
   call(my_transform<decltype(f2_2)>,&v[0],&v[1],&out[0],f2_2);
   call(my_transform<decltype(f2_3)>,&v[0],&v[1],&out[0],f2_3);

   accumulate(begin(v),end(v), record{}, f3_1 );
   accumulate(begin(v),end(v), record{}, f3_2 );
   accumulate(begin(v),end(v), record{}, f3_3 );
   call(accumulate<decltype(begin(v)),record,decltype(&f3_1)>,begin(v),end(v),record{},f3_1);
   call(accumulate<decltype(begin(v)),record,decltype(f3_2)>,begin(v),end(v),record{},f3_2);
   call(accumulate<decltype(begin(v)),record,decltype(f3_3)>,begin(v),end(v),record{},f3_3);
   r = my_accumulate(&v[0],&v[1],record{}, f3_1 );
   r = my_accumulate(&v[0],&v[1],record{}, f3_2 );
   r = my_accumulate(&v[0],&v[1],record{}, f3_3 );
   r = call(my_accumulate<decltype(f3_1)>,&v[0],&v[1],record{},f3_1);
   r = call(my_accumulate<decltype(f3_2)>,&v[0],&v[1],record{},f3_2);
   r = call(my_accumulate<decltype(f3_3)>,&v[0],&v[1],record{},f3_3);

   cin.get();
   return 0;
}

