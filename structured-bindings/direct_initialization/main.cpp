#include <iostream>
#include <tuple>

/**
   3 Simple C++17 Features That Will Make Your Code Simpler
   https://www.fluentcpp.com/2018/06/19/3-simple-c17-features-that-will-make-your-code-simpler/
*/

using namespace std;

int main()
{
   {
      auto ch  = '#';
      auto i   = 0;
      auto b   = true;
   }
   {
      auto [ch,i,b] = tuple{'#',0,true};
   }
   {
      // for(char ch = '#', int i = 0, bool b = true; i < 10; ++i) {} won't compile
      for (auto[ch,i,b] = tuple{'#',0,true } ; i < 10; ++i) {}
   }
}
