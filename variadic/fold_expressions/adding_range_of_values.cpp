#include <utility>

template <typename Container, typename... Values>
void push_back(Container& c, Values... vals)
{
   (c.push_back(std::forward<Values>(vals)),...);
}

//// Example of Usage:

#include <vector>
#include <list>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <string>
#include <deque>

using namespace std;

template <typename Container>
void print(const Container& c)
{
   for_each(begin(c),end(c),[](const auto& v){
      cout << v << ", ";
   });
   cout << endl; 
}

class only_moveable_type
{
   string s_;
public:
   explicit only_moveable_type(const char* s) : s_(s) {}
   ~only_moveable_type()                                    = default;
   only_moveable_type(only_moveable_type&&)                 = default;
   only_moveable_type(const only_moveable_type&)            = delete;
   only_moveable_type& operator=(const only_moveable_type&) = delete;
   only_moveable_type& operator=(only_moveable_type&&)      = delete;
   only_moveable_type()                                     = delete;

   friend ostream& operator<<(ostream& out, const only_moveable_type& mt) {
      return out << mt.s_;
   }
};

inline only_moveable_type operator""_mt(const char* s, size_t)
{
   return only_moveable_type(s);
}


int main()
{
   {  vector<int> v;
      push_back(v,1,2,3,4,5,6,7,8,9,0);
      print(v);
   }
   {  list<double> l;
      push_back(l,1,2,3,4,5,6,7,8,9,0);
      print(l);
   }
   {  string s;
      push_back(s,'a','b','c','d','e','F','G','H','I','J');
      print(s);
   }
   {  deque<only_moveable_type> d;
      push_back(d,"C++17"_mt,"fold"_mt,"expressions"_mt);
      print(d);
   }
}

