#include <string>
#include <iostream>
#include <cassert>
#include <stdexcept>

#ifdef _MSC_VER
	#define noexcept throw()
	#pragma warning( disable : 4702 )  // warning C4702: unreachable code
#endif


using namespace std;

namespace
{

struct A
{
    int         a = 1;
    const int   b = a+1;
    int         c{b+1};
    int         d;
    const int   f=d++;
    const int   e=d++;

    A(int d_, int e_) : d(d_), e(e_) {};
    A(const A&) = delete;
    A& operator=(const A&) = delete;
};

template <typename OUTPUT_STREAM_T>
OUTPUT_STREAM_T& operator<<(OUTPUT_STREAM_T& out, const A& a)
{
    out << "{a=" << a.a << ",b=" << a.b << ",c=" << a.c << ",d=" << a.d << ",f=" << a.f << ",e=" << a.e << "}";
    return out;
}

void test_data_member_init()
{
    cout << "--- test_data_member_init ---" << endl;
    const A a{10,0};
    cout << a << endl;
}

class Rectangle
{
    size_t width_{0};
    size_t height_{0};

public:
    Rectangle(size_t w, size_t h) noexcept :
         width_(w)
        ,height_(h)
    {
        assert(width_ && height_ && "zero width_ or height_");
        cout << "Rectangle::Target ctor" << endl;
    }
    Rectangle(size_t side) noexcept :
        Rectangle(side,side)
    {
        cout << "Rectangle::Delegate ctor" << endl;
    }

    Rectangle(string) :
        Rectangle(123)
    {
        throw runtime_error("Rectangle(string) ctor: exception");
		// MSVC	warning C4702: unreachable code
	}


    ~Rectangle()
    {
        cout << "~Rectangle" << endl;
    }

    size_t width()  const noexcept { return width_; }
    size_t height() const noexcept { return height_; }

};

class DecoratedRectangle : public Rectangle
{
public:
#if _MSC_VER || !(__GNUG__>4 && __GNUC_MINOR__>=8)
    DecoratedRectangle(size_t side) : Rectangle(side) {}
#else
    using Rectangle::Rectangle; // <-- Inheriting Constructors have been available in GCC since version 4.8; Visual C++ 2013 doesn't support
#endif
};


template <typename OUTPUT_STREAM_T>
inline OUTPUT_STREAM_T& operator<<(OUTPUT_STREAM_T& out, const Rectangle& r)
{
    out << "{w=" << r.width() << ",h=" << r.height() << "}";
    return out;
}


void test_delegate_ctor()
{
    cout << "--- test_delegate_ctor ---" << endl;
    {
        const Rectangle r{10};
        cout << r << endl;
    }

    try
    {
        const Rectangle r{"exception test"};
        cout << r << endl;
    }
    catch(exception& e)
    {
        cout << "caught exception:  " << e.what() << endl;
    }
}

void test_inheritable_ctor()
{
    cout << "--- test_inheritable_ctor ---" << endl;
    const DecoratedRectangle r{111};
    cout << r << endl;
}

}   // end of anonymous namespace


int main()
{
    test_data_member_init();
    test_delegate_ctor();
    test_inheritable_ctor();

   cout << "Press any key + <enter> to exit" << endl;
   cin.get(); 
}
