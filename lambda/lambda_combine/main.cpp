#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <algorithm>

namespace logical_combine
{

template <typename LogicalOp, typename L, typename R>
auto unite(LogicalOp op, L l, R r)
{
   return [=](auto... ps){
      return op(l(ps...),r(ps...)); 
   };
} 

template <typename L, typename R>
auto operator &&(L l, R r)
{
   return unite(std::logical_and<>(),l,r);
}

template <typename L, typename R>
auto operator ||(L l, R r)
{
   return unite(std::logical_or<>(),l,r);
}

}  // namespace logical_combine


using namespace std;

auto is_odd    = [](auto x) { return x%2; };
auto is_even   = [](auto x) { return !(x%2); };
auto in_range  = [](auto min, auto max) { 
                        return [=](auto x) {
                           return min<=x && x<=max; 
                        }; 
                     };

int main()
{
   vector<int> source = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
   vector<int> destination;

   using namespace logical_combine;
   copy_if(  begin(source),end(source)
            ,back_inserter(destination)
            ,(in_range(2,9) && is_odd) || (in_range(11,15) && is_even)
   );

   for(auto i : destination)
      cout << i << " ";
}