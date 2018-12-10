/*
*/

///////////////////////////////////////////////////

#include <iterator>
#include <iostream>
#include <initializer_list>
#include <numeric>

using namespace std;

int main()
{
   const auto seq = {1,2,3,4,5,6};

   {  cout << endl << "--- inception point:" << endl;

      const auto res = accumulate(begin(seq), end(seq), ostream_iterator<int>(cout,",")
         ,[](auto it, int v){
            if(0==v%2) {               // <-- 1) predicate: even
               const auto res =  2*v;  // <-- 2) action: twice
               *it++ = res;            // <-- 3) accumulation: copy + advance
            }
            return it;
      });
   }

   {  cout << endl << "--- iteration 1:" << endl;

      const auto even             = [](int v) { return 0==v%2; };
      const auto twice            = [](int v) { return 2*v; };
      const auto copy_and_advance = [](auto it, int v) { *it++ = v; };

      const auto res = accumulate(begin(seq), end(seq), ostream_iterator<int>(cout,",")
         ,[even,twice,copy_and_advance](auto it, int v){ // <-- 0) capturing 3 lambdas
            if(even(v)) {                                // <-- 1) predicate
               const auto res =  twice(v);               // <-- 2) action
               copy_and_advance(it,res);                 // <-- 3) accumulation
            }
            return it;
      });
   }

   {  cout << endl << "--- iteration 2:" << endl;

      const auto even             = [](int v) { return 0==v%2; };
      const auto twice            = [](int v) { return 2*v; };
      const auto copy_and_advance = [](auto it, int v) { *it++ = v; };
      const auto filter = [even,twice,copy_and_advance](auto it, int v) { // <-- 0) capturing 3 lambdas
         if(even(v)) {                                // <-- 1) predicate
            const auto res =  twice(v);               // <-- 2) action
            copy_and_advance(it,res);                 // <-- 3) accumulation
         }
         return it;
      };

      const auto res = accumulate(begin(seq), end(seq), ostream_iterator<int>(cout,",")
         ,filter
      );
   }

   {  cout << endl << "--- iteration 3:" << endl;

      const auto even             = [](int v) { return 0==v%2; };
      const auto twice            = [](int v) { return 2*v; };
      const auto copy_and_advance = [](auto it, int v) { *it++ = v; };
      const auto filter = [even,twice](auto accumulation) { // <-- 0) capturing 2 lambdas
         return [=](auto it, int v) {
            if(even(v)) {                                // <-- 1) predicate
               const auto res =  twice(v);               // <-- 2) action
               accumulation(it,res);                     // <-- 3) 
            }
            return it;
         };
      };

      const auto res = accumulate(begin(seq), end(seq), ostream_iterator<int>(cout,",")
         ,filter(copy_and_advance)
      );
   }

   {  cout << endl << "--- iteration 4:" << endl;

      const auto even             = [](int v) { return 0==v%2; };
      const auto twice            = [](int v) { return 2*v; };
      const auto copy_and_advance = [](auto it, int v) { *it++ = v; };
      const auto filter = [even](auto action) { // <-- 0) capturing 1 lambda
         return [=](auto accumulation) {
            return [=](auto it, int v) {
               if(even(v)) {                                // <-- 1) predicate
                  const auto res =  action(v);              // <-- 2)
                  accumulation(it,res);                     // <-- 3) 
               }
               return it;
            };
         };
      };

      const auto res = accumulate(begin(seq), end(seq), ostream_iterator<int>(cout,",")
         ,filter(twice)(copy_and_advance)
      );
   }

   {  cout << endl << "--- iteration 5:" << endl;

      const auto even             = [](int v) { return 0==v%2; };
      const auto twice            = [](int v) { return 2*v; };
      const auto copy_and_advance = [](auto it, int v) { *it++ = v; };
      const auto filter           = [](auto predicate) { //    <-- 0) no capturing
         return [=](auto action) {
            return [=](auto accumulation) {
               return [=](auto it, int v) {
                  if(predicate(v)) {                           // <-- 1) predicate
                     const auto res =  action(v);              // <-- 2)
                     accumulation(it,res);                     // <-- 3) 
                  }
                  return it;
               };
            };
         };
      };

      const auto res = accumulate(begin(seq), end(seq), ostream_iterator<int>(cout,",")
         ,filter(even)(twice)(copy_and_advance)
      );
   }

   {  cout << endl << "--- iteration 6:" << endl;

      const auto even             = [](int v) { return 0==v%2; };
      const auto twice            = [](int v) { return 2*v; };
      const auto copy_and_advance = [](auto it, int v) { *it++ = v; return it; };
      const auto filter           = [](auto predicate) {
         return [=](auto action) {
            return [=](auto accumulation) {
               return [=](auto it, int v) {
                  return predicate(v)? accumulation(it,action(v)) : it;
               };
            };
         };
      };

      const auto res = accumulate(begin(seq), end(seq), ostream_iterator<int>(cout,",")
         ,filter(even)(twice)(copy_and_advance)
      );
   }

   {  cout << endl << "--- iteration 7:" << endl;

      const auto filter           = [](auto predicate) {
         return [=](auto action) {
            return [=](auto accumulation) {
               return [=](auto it, int v) {
                  return predicate(v)? accumulation(it,action(v)) : it;
               };
            };
         };
      };

      const auto res = accumulate(begin(seq), end(seq), ostream_iterator<int>(cout,",")
         ,filter([](int v)          { return 0==v%2; })
                ([](int v)          { return 2*v; })
                ([](auto it, int v) { *it++ = v; return it; })
      );
   }

}

