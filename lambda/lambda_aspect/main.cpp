#include <string>
#include <iostream>

#ifdef _MSC_VER
   #pragma warning( push )
   #pragma warning( disable : 4265 )  // warning C4265: 'std::_Func_base<_Ret,Widget &>': class has virtual functions, but destructor is not virtual
#endif
#include <functional>
#ifdef _MSC_VER
   #pragma warning( pop )
#endif


// http://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Execute-Around_Pointer


using namespace std;


struct Widget
{
    Widget()                = default;
    Widget(const Widget&)   = delete;

    void    draw() const                { cout << "Widget::draw("<< data_ << ")" << endl; }
    void    value(size_t v) noexcept    { data_ = v; }
    size_t  value() const   noexcept    { return data_; }
private:
    size_t  data_ = 0;
};

struct A1
{
    template <typename T> void epilogue(T& o) { cout << "A1{" << endl; o.value(o.value()+1); }
    template <typename T> void prologue(T& o) { cout << "}A1" << endl; o.value(o.value()-1); }
};

struct A2
{
    template <typename T> void epilogue(T& o) { cout << "A2{" << endl; o.value(o.value()+2); }
    template <typename T> void prologue(T& o) { cout << "}A2" << endl; o.value(o.value()-2); }
};

struct A3
{
    template <typename T> void epilogue(T& o) { cout << "A3{" << endl; o.value(o.value()+3); }
    template <typename T> void prologue(T& o) { cout << "}A3" << endl; o.value(o.value()-3); }
};

//////////////////////////////////

using signature_t = function<void(Widget&)>;

inline signature_t draw()
{
    return [] (Widget& w) { w.draw(); };
}

template <typename ASPECT, typename PARAMETER>
class guard
{
    using aspect_t      = ASPECT;
    using parameter_t   = PARAMETER;
    parameter_t param_;
public:
    guard (parameter_t p) : param_(p)   { aspect_t{}.epilogue(param_); static_assert(std::is_reference<parameter_t>::value,"parameter must be a reference"); }
    ~guard ()                           { aspect_t{}.prologue(param_); }
};

template <typename ASPECT, typename F>
signature_t aspect(F f)
{
    using aspect_t      = ASPECT;
    using argument_t    = typename F::argument_type;

    return [f] (argument_t a)
        {
            static_assert(std::is_reference<argument_t>::value,"parameter must be a reference");
            guard<aspect_t,argument_t> g(a);
            return f(a);
        };
}

int main(int /*argc*/, char** /*argv[]*/)
{
// http://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Execute-Around_Pointer
    auto c1 = draw();
    auto c2 = aspect<A1>(c1);
    auto c3 = aspect<A3>(c2);
    auto c4 = aspect<A2>(c3);

    Widget w{};
    c4(w);
    c1(w);

    cout << "Press any key + <enter> to exit" << endl;
    cin.get();

    return 0;
}
