/**
   'min' & 'max' compile time math functions with any numbers of arguments   
*/
#include <algorithm>
#include <cstddef>
#include <utility>

namespace private_
{

template< typename BinaryOperation, typename T > 
constexpr auto apply(BinaryOperation op, T a, T b) {
   return op(a,b);
}

template< typename BinaryOperation, typename T, typename... U > 
constexpr auto apply(BinaryOperation op, T a, U... bs) {
   return apply(op,a,apply(op,bs...));
}

template< typename BinaryOperation, typename Container, std::size_t... Idx > 
constexpr auto apply(BinaryOperation op, const Container& c, std::index_sequence<Idx...>) {
   return apply(op,c[Idx]...);
}

namespace bin_op
{
   const auto min = [](auto x, auto y){ return std::min(x,y); };
   const auto max = [](auto x, auto y){ return std::max(x,y); };
}  // end of namespace bin_op

} // end of namespace private_

template<typename T, typename... U > 
constexpr auto min(T a, U... bs) {
   using namespace private_;
   return apply(bin_op::min,a,bs...);
}

template<typename T, std::size_t N > 
constexpr auto min(const T(&arr)[N]) {
   using namespace private_;
   return apply(bin_op::min,arr,std::make_index_sequence<N>{});
}

template<typename T, typename... U > 
constexpr auto max(T a, U... bs) {
   using namespace private_;
   return apply(bin_op::max,a,bs...);
}

template<typename T, std::size_t N > 
constexpr auto max(const T(&arr)[N]) {
   using namespace private_;
   return apply(bin_op::max,arr,std::make_index_sequence<N>{});
}

int main()
{
   static_assert(0==min(0,1,2,3,4,5,6,7,8,9));
   static_assert(1==min(2,1));
   static_assert(9==max(0,1,2,3,4,5,6,7,8,9));
   static_assert(2==max(2,1));

   constexpr int arr1[] = {0,1,2,3,4,5,6,7,8,9}; 
   constexpr int arr2[] = {2,1}; 
   static_assert(0==min(arr1));
   static_assert(1==min(arr2));
   static_assert(9==max(arr1));
   static_assert(2==max(arr2));
}
