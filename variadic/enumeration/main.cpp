#include <string>
#include <iostream>

/**
	Idea comes from http://scrutator.me/post/2013/01/18/template-innovations.aspx
*/

using namespace std;

inline string str(bool in)
{
    return in? "1" : "0";
}

namespace recursion_class
{

template <bool... bits> struct printer;

template <bool head, bool... tails>
struct printer<head,tails...>
{
    static string c_str() { return str(head) + printer<tails...>::c_str(); }
};

template <>
struct printer<>
{
    static string c_str() { return ""; }
};

template <bool... bits>
string test()
{
    return printer<bits...>::c_str();
}

} // recursion_class namespace

namespace recursion_function
{

template <bool Bit>
string test()
{
    return str(Bit);
}

template <bool First, bool Second, bool... Tails>
string test()
{
	return test<First>() + test<Second, Tails...>();
}

} // recursion_function

namespace init_list
{

template <bool... bits>
string test()
{
	auto list = { bits... };
	string out;
	for (auto i : list)
		out += str(i);
	return out;
}

} // initializer_list


namespace argument_list
{
	template <bool Bit>
	string to_str()
	{
		return str(Bit);
	}

	template<typename... Args> inline void stub(Args&&...) {}


	template <bool... bits>
	string test()
	{
		string out;
		stub((out+=to_str<bits>())...);
		return out;
	}

} // argument_list

namespace fold_expressions // since C++17
{
   // http://en.cppreference.com/w/cpp/language/fold
   // http://scrutator.me/post/2017/08/11/cpp17_lang_features_p1.aspx

	template <bool... bits>
	string test1() // unary left fold with 'comma' operator 
	{
		string out;
		(... ,(out+=str(bits)));
		return out;
	}

	template <bool... bits>
	string test2() // binary left fold with operator +=
	{
		string out;
      (out += ... += str(bits));
		return out;
	}

}

int main(int /*argc*/, char** /*argv[]*/)
{
	cout << "recursion_class: " << recursion_class::test<1, 1, true, false, 0, 1, false>() << endl;
	cout << "recursion_function: " << recursion_function::test<1, 1, true, false, 0, 1, false>() << endl;
	cout << "initr_list: " << init_list::test<1, 1, true, false, 0, 1, false>() << endl;
	cout << "argument_list: " << argument_list::test<1, 1, true, false, 0, 1, false>() << endl;
	cout << "fold_expressions [unary left]: " << fold_expressions::test1<1, 1, true, false, 0, 1, false>() << endl;
	cout << "fold_expressions [binary left]: " << fold_expressions::test2<1, 1, true, false, 0, 1, false>() << endl;

    cout << "Press any key + <enter> to exit" << endl;
    cin.get();
    return 0;
}
