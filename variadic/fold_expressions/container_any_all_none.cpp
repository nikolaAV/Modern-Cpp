#include <utility>
#include <algorithm>

template <typename Container, typename Value>
bool contains(const Container& c, const Value& v) {
   return std::end(c) != std::find(std::begin(c),std::end(c),v);
}

template <typename Container, typename... Values>
bool contains_any(const Container& c, Values&&... vals)
{
   return ( ... || contains(c,vals));
}

template <typename Container, typename... Values>
bool contains_all(const Container& c, Values&&... vals)
{
   return ( ... && contains(c,vals));
}

template <typename Container, typename... Values>
bool contains_none(const Container& c, Values&&... vals)
{
   return !contains_all(c,std::forward<Values>(vals)...);
}

//// Example of Usage:

#include <initializer_list>
#include <iostream>

using namespace std;

int main()
{
   const initializer_list<int> c = {0,1,2,3,4,7,9};

   cout << contains_any(c,100,50,10,8) << endl; 
   cout << contains_any(c,100,50,10,7) << endl; 
   cout << contains_all(c,100,50,10,7) << endl; 
   cout << contains_all(c,9,1,4,3)     << endl; 
   cout << contains_none(c,100,50,10,8)<< endl; 
}

