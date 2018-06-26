#include <iostream>
#include <initializer_list>
#include <string_view>

namespace multicall
{

auto make = [](auto... funcs) {
   return [=](auto... params) {
      // std::initializer_list<int> { ((void)funcs(params...),0)...}; before C++17 (fold expressions)
      (funcs(params...),...); // since C++17, but for Microsoft C/C++ Compiler Ver. 19.14 and earlier
  };
};

}  // namespace multicall

using namespace std;

void foo(string_view sv, double data)
{
   cout << "Do something useful with: " << sv.data() << " & " << data << endl; 
}

void prologue(string_view sv, double data)
{
   cout << "foo(" << sv.data() << "," << data << ") is being invoked ..." << endl; 
}

void epilogue(string_view, double)
{
   cout << "commit changes!" << endl; 
}

int main()
{
   auto f = multicall::make(prologue,foo,epilogue);   
   f("Pi",3.1456);
}
