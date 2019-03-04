#include <iostream>
#include <stdexcept>

constexpr unsigned char ascii_expects(int ch)
{ 
   return 0x00 <= ch && ch <= 0x7F? // https://en.cppreference.com/w/cpp/language/ascii
         static_cast<unsigned char>(ch)
      :  throw std::runtime_error{"no ASCII code"}
   ;
}

using namespace std;

int main()
{
   constexpr auto copmile_ok  = ascii_expects(' ');
      // Depending on compiler, error message can be
      // Visual C++: expression did not evaluate to a constant 
      // GCC: expression '<throw-expression>' is not a constant expression
      // Clang: constexpr variable 'copmile_err' must be initialized by a constant expression
// constexpr auto copmile_err = ascii_expects('\xAA'); // 

   try
   {
      int space = ' ';
      int xAA   = '\xAA';

      cout << "ascii_expects(space): " << ascii_expects(space) << endl;
      cout << "ascii_expects(xAA): "   << ascii_expects(xAA) << endl;
   }
   catch(const exception& e) {
      cout << "exception: " << e.what() << endl;
   }

}

