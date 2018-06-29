
constexpr auto inner_product = [](auto... txs) constexpr {
   return [txs...](auto... tys) { 
      return [tys...,txs...](auto f) {
         (f(txs,tys),...); 
      };
   };
};

#include <iostream>
using namespace std;

int main()
{
   constexpr auto prod = inner_product(1,2,3)('a','b','c');
   prod([](int x, char y) { 
      cout << "{" << x << "," << y << "}"; 
   });
}
