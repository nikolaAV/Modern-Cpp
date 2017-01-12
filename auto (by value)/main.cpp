#include <iostream>
#include <typeinfo>

/**
	for more details, see
	Effective Modern C++ by Scott Meyers
	Item 4: Know how to view deduced types., page 30
*/

using namespace std;

template <typename T> struct type_name;   // use it to detect type name in compile-time as an error

int main()
{
	const int  theNumber {44};

	auto   x  =  theNumber;
	auto   y  = &theNumber;

//	type_name<decltype(x)> t; // error: aggregate 'type_name<int> t' has incomplete type and cannot be defined
//	type_name<decltype(y)> t; // error: aggregate 'type_name<const int*> t' has incomplete type and cannot be defined 

	cout  << "auto x =  theNumber --> " << typeid(x).name() << endl 
         << "auto x = &theNumber --> " << typeid(y).name() << endl;

   cout << "Press any key + <enter> to exit" << endl;
   cin.get();
}
