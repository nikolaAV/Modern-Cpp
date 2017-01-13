#include <string>
#include <iostream>
#include <vector>

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4265 )  // warning C4265: 'std::_Func_base<_Ret,Widget &>': class has virtual functions, but destructor is not virtual
#endif
#include <functional>
#ifdef _MSC_VER
#pragma warning( pop )
#endif

/**
   Idia from: https://habrahabr.ru/post/151504/
*/


using namespace std;


template <typename T>
struct ContainerConcept
{
    typedef T   value_type;

    value_type&  operator[]  (size_t i) {return func_get_(i);}
    size_t size     () const            {return func_size_();}

private:
    function<value_type&(size_t)>   func_get_;
    function<size_t()>              func_size_;

public:
    template <typename C>
    ContainerConcept(C& c)
        :    func_get_  ( [&c](size_t i) -> value_type& { return c[i];} )
            ,func_size_ ( [&c]() {return c.size();} )
    {
    }

//    ContainerConcept(const ContainerConcept&) = delete;
    ContainerConcept& operator=(const ContainerConcept&) = delete;
};

template <typename T>
void do_print(const T& v)
{
    cout << v;
}

template <typename T>
void enumerate(ContainerConcept<T> c)
{
    for(size_t i = 0; i < c.size(); ++i)
        do_print(c[i]);
}

template <typename CONTAINER_T>
void enumerate(CONTAINER_T& c)
{
    typedef typename CONTAINER_T::value_type value_type;
    enumerate<value_type>(c);
}


int main(int /*argc*/, char** /*argv[]*/)
{
    {
    vector<int> v{1,2,3,4,5,6,7,8,9};
    enumerate(v);
    cout << endl;
    }
    {
    vector<const char*> v{"C++","0x",":","Concepts"};
    enumerate(v);
    cout << endl;
    }


    cout << "Press any key + <enter> to exit" << endl;
    cin.get();
    return 0;
}
