#include <string>
#include <iostream>
#include <tuple>

using namespace std;

namespace tuple_
{

// how to enumerate std::tuple
// http://cpplove.blogspot.com/2012/07/printing-tuples.html

template<std::size_t> struct int_type {};

template <typename TUPLE_T, typename VISITOR_T, size_t TUPLE_ARG_REVERSE_POS>
void visit(const TUPLE_T& t, const VISITOR_T& visitor, int_type<TUPLE_ARG_REVERSE_POS>)
{
    visitor(std::get<std::tuple_size<TUPLE_T>::value-TUPLE_ARG_REVERSE_POS>(t));
    visit(t,visitor,int_type<TUPLE_ARG_REVERSE_POS-1>{});
}

template <typename TUPLE_T, typename VISITOR_T>
void visit(const TUPLE_T& t, const VISITOR_T& visitor, int_type<1>)
{
    visitor(std::get<std::tuple_size<TUPLE_T>::value-1>(t));
}

template <typename VISITOR_T, typename... TUPLE_ARGS>
// requires C++0x concept::FunctionObject<VISITOR_T>, see http://en.cppreference.com/w/cpp/concept/FunctionObject
// with only argument of any type: template <typename T> VISITOR_T::operator()(const T& arg) {...}
void for_each(const std::tuple<TUPLE_ARGS...> t,const VISITOR_T& visitor)
{
    visit(t,visitor,int_type<sizeof...(TUPLE_ARGS)>());
}

} // namespace: tuple_


struct UserType
{
    explicit UserType(size_t v) : val_(v) {}
    size_t val_;
};

template<typename OUTSTREAM_T>
OUTSTREAM_T& operator<<(OUTSTREAM_T& out, const UserType& ut)
{
    out << ut.val_;
    return out;
}

template <typename OUTSTREAM_T>
struct VisitorOutput
{
    OUTSTREAM_T& out_;
    explicit VisitorOutput(OUTSTREAM_T& out) : out_(out) {}

    template <typename T>
    void operator()(const T& v) const
    {
        out_ << v << ", ";
    }

    VisitorOutput() = delete;
    VisitorOutput& operator=(const VisitorOutput&) = delete;
};

template<typename OUTSTREAM_T, typename... TUPLE_ARGS>
OUTSTREAM_T& operator<<(OUTSTREAM_T& out, const std::tuple<TUPLE_ARGS...>& t)
{
    out << "tuple[" << sizeof...(TUPLE_ARGS) << "]: {";
    tuple_::for_each(t,VisitorOutput<OUTSTREAM_T>{out});
    out << "}";
    return out;
}

int main(int /*argc*/, char** /*argv[]*/)
{
    auto t = make_tuple(1,2.,"3",UserType{4});
	cout << t << endl;

    cout << "Press any key + <enter> to exit" << endl;
    cin.get();
    return 0;
}
