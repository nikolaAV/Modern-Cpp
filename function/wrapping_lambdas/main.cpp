#include <string>
#include <iostream>
#include <vector>
#include <functional>

using namespace std;

struct circle
{
   const char* draw() const { return "I'm a circle"; }
};

struct square
{
   const char* draw() const { return "I'm a square"; }
};

struct triangle
{
   const char* draw() const { return "I'm a triangle"; }
};

using shape                      = function<const char*(void)>; 
using heterogeneous_container_t  = vector<shape>; 

int main()
{
   heterogeneous_container_t v = {
       [c=circle{}]()     { return c.draw(); }
      ,[s=square{}]()     { return s.draw(); }
      ,[t=triangle{}]()   { return t.draw(); }
   };
   for(const auto& s:v)
      cout << s() << endl;
}