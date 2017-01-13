#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <type_traits>

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4265 )  // warning C4265: 'std::_Func_base<_Ret,Widget &>': class has virtual functions, but destructor is not virtual
#endif
#include <functional>
#ifdef _MSC_VER
#pragma warning( pop )
#endif


/**
   Idea from https://habrahabr.ru/post/304728/
*/

using namespace std;

namespace tradition
{   // based on generic calss templates, no concepts

//C++0x IntContainerConcept
//{
//    size_t    size()  const;
//    void      push_back(int); 
//    int       back()  const;
//    void      pop_back(); 
//    bool      empty() const;
//};


template <typename CONTAINER_T>
//      requires ContainerConcept<CONTAINER_T>
// or   template<IntContainerConcept CONTAINER_T>
inline void init(CONTAINER_T& c)
{
    for (int i = 0; i < 10; ++i)
        c.push_back(i);
}

template <typename CONTAINER_T>
void reverse_enumerate(CONTAINER_T& c)
{
    cout << "elements: " << c.size() << endl;
    while (!c.empty())
    {
        cout << c.back() << " ";
        c.pop_back();
    }
    cout << endl;
}

}   // namespace 'tradition'

namespace proxy
{   // based on template function spesializations

    typedef size_t(*f_size_t)(void*);
    typedef void(*f_push_back_t)(void*, int);
    typedef int(*f_back_t)(void*);
    typedef void(*f_pop_back_t)(void*);
    typedef bool(*f_empty_t)(void*);

    struct ContainerConcept
    {
        size_t    size()                const   { return f_size_(p_); }
        void      push_back(int val)            { f_push_back_(p_, val); }
        int       back()                const   { return f_back_(p_); }
        void      pop_back()                    { f_pop_back_(p_); }
        bool      empty() const                 { return f_empty_(p_); }

        template <typename CONTAINER_T>
        ContainerConcept(CONTAINER_T& c)
            : p_(&c)
            , f_size_(_size_<CONTAINER_T>)
            , f_push_back_(_push_back_<CONTAINER_T>)
            , f_back_(_back_<CONTAINER_T>)
            , f_pop_back_(_pop_back_<CONTAINER_T>)
            , f_empty_(_empty_<CONTAINER_T>)
        {}

        ContainerConcept(ContainerConcept&& other)
            : p_(move(other.p_))
            , f_size_(move(other.f_size_))
            , f_push_back_(move(other.f_push_back_))
            , f_back_(move(other.f_back_))
            , f_pop_back_(move(other.f_pop_back_))
            , f_empty_(move(other.f_empty_))
        {}

        ContainerConcept(const ContainerConcept& other) = delete;
        ContainerConcept& operator=(const ContainerConcept& other) = delete;

    private:
        void*           p_;
        f_size_t        f_size_;
        f_push_back_t   f_push_back_;
        f_back_t        f_back_;
        f_pop_back_t    f_pop_back_;
        f_empty_t       f_empty_;

    private:
        template<typename CONTAINER_T>
        static size_t _size_(void* c)
        {
            return static_cast<CONTAINER_T*>(c)->size();
        }

        template<typename CONTAINER_T>
        static void _push_back_(void* c, int val)
        {
            static_cast<CONTAINER_T*>(c)->push_back(val);
        }

        template<typename CONTAINER_T>
        static int _back_(void* c)
        {
            return static_cast<CONTAINER_T*>(c)->back();
        }

        template<typename CONTAINER_T>
        static void _pop_back_(void* c)
        {
            static_cast<CONTAINER_T*>(c)->pop_back();
        }

        template<typename CONTAINER_T>
        static bool _empty_(void* c)
        {
            return static_cast<CONTAINER_T*>(c)->empty();
        }
    };

    inline void init(ContainerConcept&& c)
    {
        for (int i = 0; i < 10; ++i)
            c.push_back(i);
    }

    void reverse_enumerate(ContainerConcept&& c)
    {
        cout << "elements: " << c.size() << endl;
        while (!c.empty())
        {
            cout << c.back() << " ";
            c.pop_back();
        }
        cout << endl;
    }

}   // namespace 'proxy'


namespace proxy2
{   // based on C++11 lambdas

    struct ContainerConcept
    {
        size_t    size()                const   { return f_size_(); }
        void      push_back(int val)            { f_push_back_(val); }
        int       back()                const   { return f_back_(); }
        void      pop_back()                    { f_pop_back_(); }
        bool      empty() const                 { return f_empty_(); }

        template <typename CONTAINER_T>
        ContainerConcept(CONTAINER_T& c)
            : f_size_       ([&c]()         { return c.size(); } )
            , f_push_back_  ([&c](int v)    { c.push_back(v); } )
            , f_back_       ([&c]()         { return c.back(); })
            , f_pop_back_   ([&c]()         { c.pop_back(); })
            , f_empty_      ([&c]()         { return c.empty(); } )
        {}

        ContainerConcept(ContainerConcept&& other)
            : f_size_       (move(other.f_size_))
            , f_push_back_  (move(other.f_push_back_))
            , f_back_       (move(other.f_back_))
            , f_pop_back_   (move(other.f_pop_back_))
            , f_empty_      (move(other.f_empty_))
        {}

        ContainerConcept(const ContainerConcept& other) = delete;
        ContainerConcept& operator=(const ContainerConcept& other) = delete;

    private:
        function<size_t()>  f_size_;
        function<void(int)> f_push_back_;
        function<int()>     f_back_;
        function<void()>    f_pop_back_;
        function<bool()>    f_empty_;
    };

    inline void init(ContainerConcept&& c)
    {
        for (int i = 0; i < 10; ++i)
            c.push_back(i);
    }

    void reverse_enumerate(ContainerConcept&& c)
    {
        cout << "elements: " << c.size() << endl;
        while (!c.empty())
        {
            cout << c.back() << " ";
            c.pop_back();
        }
        cout << endl;
    }

}   // namespace 'proxy2'


namespace proxy3
{   // based on C++11 decltype, enable_if and is_member_function_pointer
    // https://habrahabr.ru/post/304728/

    template <typename CONTAINER_T
                , typename = typename enable_if<is_member_function_pointer<decltype(&CONTAINER_T::empty)>::value>::type
                , typename = typename enable_if<is_member_function_pointer<decltype(&CONTAINER_T::size)>::value>::type
                , typename = typename enable_if<is_member_function_pointer<decltype(&CONTAINER_T::pop_back)>::value>::type
            //    , typename = typename enable_if<is_member_function_pointer<decltype(&CONTAINER_T::push_back)>::value>::type
            //    , typename = typename enable_if<is_member_function_pointer<decltype(&CONTAINER_T::back)>::value>::type
    >
    using ContainerConcept = CONTAINER_T;

    template<typename CONTAINER_T>
    inline void init(ContainerConcept<CONTAINER_T>& c)
    {
        for (int i = 0; i < 10; ++i)
            c.push_back(i);
    }

    template<typename CONTAINER_T>
    void reverse_enumerate(ContainerConcept<CONTAINER_T>& c)
    {
        cout << "elements: " << c.size() << endl;
        while (!c.empty())
        {
            cout << c.back() << " ";
            c.pop_back();
        }
        cout << endl;
    }

}   // namespace 'proxy3'



void test_tradition()
{
    using namespace tradition;

    vector<int> v;
    init(v);
    reverse_enumerate(v);

    list<int> l;
    init(l);
    reverse_enumerate(l);
}

void test_proxy()
{
    using namespace proxy;

    vector<int> v;
    init(v);
    reverse_enumerate(v);

    list<int> l;
    init(l);
    reverse_enumerate(l);
}

void test_proxy2()
{
    using namespace proxy2;

    vector<int> v;
    init(v);
    reverse_enumerate(v);

    list<int> l;
    init(l);
    reverse_enumerate(l);
}

void test_proxy3()
{
    using namespace proxy3;

    vector<int> v;
    init(v);
    reverse_enumerate(v);

    list<int> l;
    init(l);
    reverse_enumerate(l);
}


int main(int /*argc*/, char** /*argv[]*/)
{
    test_tradition();
    test_proxy();
    test_proxy2();   

    cout << "Press any key + <enter> to exit" << endl;
    cin.get();
    return 0;
}
