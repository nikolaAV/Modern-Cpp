#include <string>
#include <iostream>
#include <tuple>

using namespace std;

namespace Cmd
{
struct A
{
    void operator()() const
    {
        cout << "A" << endl;
    }
};
struct B
{
    void operator()() const
    {
        cout << "B" << endl;
    }
};
struct C
{
    void operator()() const
    {
        cout << "C" << endl;
    }
};
struct Null
{
    void operator()() const
    {
        cout << "Unknown command" << endl;
    }
};

} // end of namespace Cmd


namespace tuple_for_each
{

// how to enumerate std::tuple
// http://cpplove.blogspot.com/2012/07/printing-tuples.html

template<size_t> struct int_{};

template<typename CMD_TUPLE, size_t Pos>
void invoke(const CMD_TUPLE& t, const char* event_name, int_<Pos>)
{
    const auto element = get<tuple_size<CMD_TUPLE>::value-Pos>(t);
    if(string{element.first}==event_name)
        element.second();
    invoke(t,event_name,int_<Pos-1>());
}

template<typename CMD_TUPLE>
void invoke(const CMD_TUPLE& t, const char* event_name, int_<1>)
{
    const auto element = get<tuple_size<CMD_TUPLE>::value-1>(t);
    if(string{element.first}==event_name)
        element.second();
    else
        Cmd::Null{}();
}

} // namespace: tuple_for_each

template <typename... CMD_LIST>
// CMD_LIST is an arguments of std::tuple<CMD_DESCRIPTOR_1,CMD_DESCRIPTOR_2,...>
// where CMD_DESCRIPTOR is std::pair<const char*, CmdT>
//  first - a string with command name
//  second - an object of any command type defined above: CmdA, CmdB, CmdC
inline void dispatch(const std::tuple<CMD_LIST...>& list, const char* event_name)
{
    tuple_for_each::invoke(list,event_name,tuple_for_each::int_<sizeof...(CMD_LIST)>());
}


int main(int /*argc*/, char** /*argv[]*/)
{
    auto cmd_list = make_tuple(
         make_pair("CmdA",Cmd::A())
        ,make_pair("CmdB",Cmd::B())
        ,make_pair("CmdC",Cmd::C())
        // TO DO
    );

    dispatch(cmd_list,"CmdC");
    dispatch(cmd_list,"Unexpected");

    cout << "Press any key + <enter> to exit" << endl;
    cin.get();
    return 0;
}
