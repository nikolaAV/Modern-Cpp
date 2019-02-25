#include <string>
#include <regex>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>

using namespace std;

string read() {
   stringstream ss;
   ss << ifstream{"Regular expressions library - cppreference.com.html"}.rdbuf();
   return ss.str();
}

int main()
{
   auto const in = read();

   /**
      Expected pattern: <a href="url" ... >text ...</a>
      \see https://en.cppreference.com/w/cpp/regex/ecmascript
   */
   const regex reg{"<a href=\"([^\"]*)\"[^<]*>([^<]*)</a>"};
   //                         link             dest
   {  // variant 1
      sregex_iterator it{begin(in), end(in), reg};      
		for (; it != sregex_iterator{}; ++it)
         cout << it->str(2) << ":\t" << it->str(1) << endl;   
   }

   {  // variant 2
      sregex_token_iterator it{begin(in), end(in), reg, {1,2}};      
		while (it != sregex_token_iterator{}) {
         const string link{*it++};
         const string dest{*it++};
         cout << dest << ":\t" << link << endl;
      }
   }
}

