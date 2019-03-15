#include <cstddef>
#include <cassert>
#include <string_view>

/**
   The International Standard Book Number (ISBN) is a unique numeric identifier for books.
   Currently, a 13-digit format is used. 
   However, as an example, we are to validate the former format that used 10 digits.
   The last of the 10 digits is a checksum. 
   This digit is chosen so that the sum of all the ten digits, each multiplied by its (integer) weight, descending from 10 to 1, is a multiple of 11.

   And ... pay attention, 
   there is a possibility to do such validation for string literals at compile time. 

   \see https://en.wikipedia.org/wiki/International_Standard_Book_Number
   \see https://github.com/nikolaAV/Modern-Cpp/tree/master/constexpr/isbn 
*/

namespace isbn10
{ 

constexpr inline std::size_t digit(char ch) noexcept {
   switch(ch) {
      case '0': return 0; 
      case '1': return 1; 
      case '2': return 2; 
      case '3': return 3; 
      case '4': return 4; 
      case '5': return 5; 
      case '6': return 6; 
      case '7': return 7; 
      case '8': return 8; 
      case '9': return 9; 
      case 'X': return 10; 
   }
   return 11;
}

constexpr inline bool allowed(std::size_t d) noexcept {
   return d <= 10;
}

constexpr inline bool validate(const char* s, std::size_t size) noexcept {
   if(10!=size)
      return false;
   return (   10*digit(s[0])
            +  9*digit(s[1])
            +  8*digit(s[2])
            +  7*digit(s[3])
            +  6*digit(s[4])
            +  5*digit(s[5])
            +  4*digit(s[6])
            +  3*digit(s[7])
            +  2*digit(s[8])
            +  1*digit(s[9])
          )
         %11==0; 
}

template <std::size_t N>
constexpr inline bool validate(const char(&s)[N]) noexcept {
   return validate(s,N-1);
}

constexpr inline bool validate(std::string_view s) noexcept {
   return validate(s.data(),s.size());
}

}  // end of namespace isbn10 

namespace isbn10_literals
{
   constexpr inline std::string_view operator"" _isbn(char const* s, std::size_t count) noexcept {
       /**
         at compile time execution context 
            - 1) if isbn10::validate is a success, assert(true) has a constant expression evaluation like static_assert
            - 2) if isbn10::validate fails, assert(false) has a run-time evaluation that leads to a compile error  
         at run-time execution context 
            assert(...) works in its usual manner
         \see https://github.com/nikolaAV/Modern-Cpp/tree/master/constexpr/invocation_context
       */
       assert(isbn10::validate(s,count)); 
       return std::string_view(s,count);
   }
}  // end of namespace isbn10_literals



///////// Example of usage:


#include <string>
#include <numeric>


void test01();
void test02();
void test03();
void test04();

int main()
{
   test01();
   test02();
   test03();
   test04();
}


namespace algo
{
   /**
      ISBN validation can be done by means std::accumulate algorithm.
      In this case the compile time checking is not possible.
   */

   inline bool validate(std::string_view s) {
      if(10 != s.size())
         return false;
      std::size_t weight{10};
      auto total = std::accumulate(std::begin(s),std::end(s),(std::size_t)0,[&weight](auto sum, auto ch){
         const auto d = isbn10::digit(ch); 
         return isbn10::allowed(d)? sum + weight--*d : 0;
      });   
      return total%11==0;
   }
}  // end of namespace algo 

void test01()
{
   using algo::validate; 

   assert(validate("9992158107"));   
   assert(validate("9971502100"));   
   assert(validate("9604250590"));   
   assert(validate("8090273416"));   
   assert(validate("8535902775"));   
   assert(validate("1843560283"));   
   assert(validate("0684843285"));   
   assert(validate("080442957X"));   
   assert(validate("0851310419"));   
   assert(validate("9386954214"));   
   assert(validate("0943396042"));   
   assert(validate("097522980X"));   

   assert(!validate("097522980X0"));   
   assert(!validate("2158107"));   
   assert(!validate("0A51310419"));   
   assert(!validate("1843560284"));   
}

void test02()
{
   using isbn10::validate; 
   using namespace std::string_literals; 

   assert(validate("9992158107"s));   
   assert(validate("9971502100"s));   
   assert(validate("9604250590"s));   
   assert(validate("8090273416"s));   
   assert(validate("8535902775"s));   
   assert(validate("1843560283"s));   
   assert(validate("0684843285"s));   
   assert(validate("080442957X"s));   
   assert(validate("0851310419"s));   
   assert(validate("9386954214"s));   
   assert(validate("0943396042"s));   
   assert(validate("097522980X"s));   

   assert(!validate("097522980X0"s));   
   assert(!validate("2158107"s));   
   assert(!validate("0A51310419"s));   
   assert(!validate("1843560284"s));   
}

void test03()
{
   using isbn10::validate; 

   static_assert(validate("9992158107"));   
   static_assert(validate("9971502100"));   
   static_assert(validate("9604250590"));   
   static_assert(validate("8090273416"));   
   static_assert(validate("8535902775"));   
   static_assert(validate("1843560283"));   
   static_assert(validate("0684843285"));   
   static_assert(validate("080442957X"));   
   static_assert(validate("0851310419"));   
   static_assert(validate("9386954214"));   
   static_assert(validate("0943396042"));   
   static_assert(validate("097522980X"));   

   static_assert(!validate("097522980X0"));   
   static_assert(!validate("2158107"));   
   static_assert(!validate("0A51310419"));   
   static_assert(!validate("1843560284"));   
}

void test04()
{
   using namespace isbn10_literals; 

   constexpr std::string_view codes[] = { 
       "9992158107"_isbn 
      ,"9971502100"_isbn   
      ,"9604250590"_isbn   
      ,"8090273416"_isbn   
      ,"8535902775"_isbn   
      ,"1843560283"_isbn   
      ,"0684843285"_isbn   
      ,"080442957X"_isbn  
      ,"0851310419"_isbn   
      ,"9386954214"_isbn   
      ,"0943396042"_isbn  
      ,"097522980X"_isbn  

//      ,"097522980X0"_isbn   <-- Compile Error
//      ,"2158107"_isbn   
//      ,"0A51310419"_isbn   
//      ,"1843560284"_isbn   
   };
}
