#include <iostream>

/**
   https://dev.to/tmr232/that-overloaded-trick-overloading-lambdas-in-c17
   https://habrahabr.ru/post/332084/
   http://cpptruths.blogspot.com/2014/03/fun-with-lambdas-c14-style-part-1.html
   https://www.bfilipek.com/2019/02/2lines3featuresoverload.html
*/

template<typename... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<typename... Ts> overloaded(Ts...) -> overloaded<Ts...>;

using namespace std;

const auto print = overloaded{
    [](bool v)          { cout << "bool: "   << v << endl; }
   ,[](char v)          { cout << "char: "   << v << endl; }
   ,[](int v)           { cout << "int: "    << v << endl; }
   ,[](long v)          { cout << "long: "   << v << endl; }
   ,[](size_t v)        { cout << "size_t: " << v << endl; }
   ,[](double v)        { cout << "char: "   << v << endl; }
   ,[](const string& v) { cout << "std::string: "<< v << endl; }
   ,[](const char* v)   { cout << "C-string: "   << v << endl; }
   ,[](auto&& v)        { cout << "by default: " << v << endl; }
};

struct point { int x,y; };
ostream& operator<<(ostream& out, const point& p)
{
   return out << "{" << p.x << "," << p.y << "}"; 
}

int main()
{
   print('A');
   print(false);
   print("Hello, World!");
   print(123);
   print(123L);
   print(point{1,2});
}
