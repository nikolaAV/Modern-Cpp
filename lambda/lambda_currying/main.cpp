#include <iostream>

using namespace std;

void foo(int a1,int a2,int a3,int a4,int a5)
{
   cout  << "foo:" 
         << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 
         << endl;
}

int main()
{
   auto f = [](int a1){
               return [=](int a2){
                  return [=](int a3){
                     return [=](int a4){
                        return [=](int a5){
                           foo(a1,a2,a3,a4,a5);
                        };
                     };
                  };
               };
            };

   f(1)(2)(3)(4)(5);
}
