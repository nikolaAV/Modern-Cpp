#include <iostream>

namespace cartesian
{

constexpr auto product_one = [](auto f, auto x, auto... ys) constexpr {
   (f(x,ys),...);
};

constexpr auto product_itself = [](auto... xs) constexpr {
   return [=](auto f){
      (product_one(f,xs,xs...),...);
   };
};

}  // end of cartesian

using namespace std;

void print(int x, int y)
{
   cout <<"("<<x<<","<<y<<")";
}

template <typename CP>
size_t sum_of_products(const CP& cp)
{
   size_t sum{0};
   cp([&sum](int x, int y) { sum += x*y; } );
   return sum;
}


int main()
{
   constexpr auto C = cartesian::product_itself(1,2,3);
   //       -1-    -2-   -3-
   // -1-  (1,1)  (1,2) (1,3)
   // -2-  (2,1)  (2,2) (2,3)
   // -3-  (3,1)  (3,2) (3,3)

  C(print);
  cout << "\nsum of all element products of cartesian product of set {1,2,3} = " << sum_of_products(C);
}