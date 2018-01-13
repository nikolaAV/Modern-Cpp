#include <iostream>
#include <utility>
#include <string>

/**
   C++17 Feature – Class Template Argument Deduction

   https://arne-mertz.de/2017/06/class-template-argument-deduction/
   http://www.bfilipek.com/2017/01/cpp17features.html#template-argument-deduction-for-class-templates
*/

const auto pair_ptr = std::pair{"Hello","World"};

namespace std {
   /**
      Example: User-defined deduction guides for std::pair

      don't wrap C-strings in std::pair
   */
   pair(char const*,char const*) -> pair<std::string,std::string>; 
}

const auto pair_str = std::pair{"Hello","World"};

using namespace std;

void foo(const char* v)
{
   cout << "type: const char* -> " << v << endl; 
}

void foo(const string& v)
{
   cout << "type: std::string -> " << v << endl; 
}


int main()
{
   foo(pair_ptr.second);   // const char*
   foo(pair_str.second);   // std::string
}
