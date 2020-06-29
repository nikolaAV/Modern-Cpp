#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "tuple_for_each.h"

using namespace std;

struct my_type
{
    explicit my_type(size_t v) : val_(v) {}
    size_t val_;
};

ostream& operator<<(ostream& out, const my_type& ut)
{
    out << ut.val_;
    return out;
}

template<typename... Args>
ostream& operator<<(ostream& out, const std::tuple<Args...>& t)
{
    out << "tuple[" << sizeof...(Args) << "]: {";
        tuple_::v1::for_each(t, [&](const auto& v) { out << v << ", "; } );
    return out << "}";
}

struct visitor
{
    string s = "tuple = {";

    template <typename Arg>
    void operator()(const Arg& a)
    {
        ostringstream out;
        out << a;
        s += out.str();
    };
};

template<typename... Args>
string to_string(const std::tuple<Args...>& t)
{
    auto out = tuple_::v2::for_each(t,visitor{});
    return out.s+="}";
}

struct toVector {
   vector<double> value;
   void operator()(const double& v) {
      value.push_back(v);
   }
};


int main(int /*argc*/, char** /*argv[]*/)
{
    const auto t = make_tuple(1,2.,"3",my_type{4});
	 cout << t << endl;                                      // <--- for_each ver.1
    cout << to_string(t) << endl;                           // <--- for_each ver.2
    tuple_::v3::for_each(t,[](const auto& v){ cout << v; });// <--- for_each ver.3
    cout << endl;
    tuple_::v4::for_each(t,[](const auto& v){ cout << v; });// <--- for_each ver.4
    cout << endl;

    auto t2 = make_tuple(3.14, 10);
    tuple_::v5::for_each(t2, [](auto& v) { v *= 2; });
    auto const res = tuple_::v5::for_each(t2, toVector{}).value;
    for (auto& s : res)
       cout << s << ", ";
    cout << endl;

    cout << "Press any key + <enter> to exit" << endl;
    cin.get();
    return 0;
}
