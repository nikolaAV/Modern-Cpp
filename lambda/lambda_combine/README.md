# Creating complex predicates with logical conjunction &  disjunction
When filtering data with generic code, we end up defining _predicates_, which tell whan data we want, and what data we do not want. Sometimes predicates are the combinations of different predicates. 
The example below shows how we can reuse existing predicates by combining them. It hepls us avoid writing a custom predicate every time we need it.
```cpp
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

  // destination: 3,5,7,9,12,14 
```
## Further informations
* [std::logical_and](https://en.cppreference.com/w/cpp/utility/functional/logical_and), [std::logical_or](https://en.cppreference.com/w/cpp/utility/functional/logical_or)
* [How to Combine Functions with Logical Operators in C++](https://www.fluentcpp.com/2020/01/31/how-to-combine-functions-with-logical-operators-in-c/) by Jonathan Boccara

## Related links
* [function concatenation with lambda expression](../lambda_concat/README.md#function-concatenation-with-lambda-expression)
* [Multicall](../lambda_multicall#callling-multiple-functions-with-the-same-input)

## Compilers
* [GCC 8.1.0](https://wandbox.org/)
* [clang 6.0.0](https://wandbox.org/)
* Microsoft (R) C/C++ Compiler 19.14 
