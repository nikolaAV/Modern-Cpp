#include <string>
#include <vector>
#include <iostream>

// http://habrahabr.ru/post/109226/

using namespace std;


template <typename CONTAINER_T, typename FUNCTION_T, typename... ARGS>
void enumerate(const CONTAINER_T& c, FUNCTION_T f, ARGS&&... args)
{
    for(const auto& item : c)
        f(item,std::forward<ARGS>(args)...);
}

template <typename CONTAINER_T, typename FUNCTION_T, typename... ARGS>
void enumerate(CONTAINER_T& c, FUNCTION_T f, ARGS&&... args)
{
    for(auto& item : c)
        f(item,std::forward<ARGS>(args)...);
}

void square(int& v)
{
    v = v*v;
}

int main(int /*argc*/, char** /*argv[]*/)
{
    typedef int element_type;
    auto print      = [](const element_type& e)                         { cout << e << ", "; };
    auto cube       = [](element_type& e)                               { e = e*e*e; };
    auto sum        = [](const element_type& e, element_type& out)      { out+=e; };
    auto offset     = [](element_type& e, element_type i)               { e+=i; };

    vector<element_type> v = {1,2,3,4,5,6,7,8,9};

    enumerate(v,print);
    cout << endl;

    element_type s{0};
    enumerate(v,sum,s);
    cout << "sum: " << s << endl;

    enumerate(v,offset,-1);
    enumerate(v,print);
    cout << endl;

    enumerate(v,cube);
    enumerate(v,print);
    cout << endl;

//    enumerate(v,[](element_type& e) {square(e);} );
    enumerate(v,square);
    enumerate(v,print);
    cout << endl;


    cout << "Press any key + <enter> to exit" << endl;
    cin.get();
    return 0;
}
