#include <numeric>
#include <algorithm>
#include <utility>

namespace stdext {

namespace aux {

// reduce: (OutputIt<U>, T) -> OutputIt<U>
template<typename T, typename OutputIt>
OutputIt reduce(OutputIt out, T const& value) {
   return *out = value, ++out;
}

// map_reduce: (T->U) -> (reduce: (OutputIt<U>, T) -> OutputIt<U>)
template <typename UnaryOperation>
auto map_reduce(UnaryOperation op) {
   return [op=std::move(op)](auto out, auto const& value){
      return reduce(out, op(value));
   };
}

// for_selected: ((T->bool),(T->U)) -> (reduce: (OutputIt<U>, T) -> OutputIt<U>)
template <typename UnaryPredicate, typename ReduceOperation>
auto for_selected(UnaryPredicate pred, ReduceOperation op) {
   return[pred = std::move(pred), map_op = std::move(op)](auto out, auto const& value) {
      return pred(value)? map_op(out, value) : out;
   };
}

} // namespace aux

template<typename InputIt, typename OutputIt, typename UnaryOperation >
OutputIt transform(InputIt first, InputIt last, OutputIt out, UnaryOperation op) {
   return std::accumulate(first, last, out, aux::map_reduce(op));
}

template<typename InputIt, typename OutputIt, typename UnaryPredicate, typename UnaryOperation >
OutputIt transform_if(InputIt first, InputIt last, OutputIt out, UnaryPredicate pred, UnaryOperation op) {
   return std::accumulate(first, last, out, aux::for_selected(pred, aux::map_reduce(op)));
}

} // namespace stdext 

////// 

#include <iostream>
#include <vector>
#include <iterator>
#include <cassert>


using namespace std;

void test1()
{
   vector<int> const in = { 0,1,2,3,4,5,6,7,8,9 };
   vector<double> expected = { 0.,2.,4.,6.,8.,10.,12.,14.,16.,18. };
   auto const op = [](auto v) {return v * 2.;};
   vector<double> result1, result2;

   std::transform(in.begin(), in.end(), back_inserter(result1), op);
   assert(result1==expected);

   stdext::transform(in.begin(), in.end(), back_inserter(result2), op);
   assert(result2 == expected);
}

void test2()
{
   vector<int> const in = { 0,1,2,3,4,5,6,7,8,9 };
   vector<double> expected = { 0.,4.,8.,12.,16. };
   auto const op = [](auto v) {return v * 2.; };
   auto const even = [](auto v) {return v % 2 == 0; };
   vector<double> result;

   stdext::transform_if(in.begin(), in.end(), back_inserter(result), even, op);
   assert(result == expected);
}

int main()
{
   test1();
   test2();
}