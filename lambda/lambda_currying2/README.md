# Playing with lambdas. Implementing transform_if using std::accumulate and lambdas.
The Standart Library provides [`std::transform`](https://en.cppreference.com/w/cpp/algorithm/transform) and [`std::copy_if`](https://en.cppreference.com/w/cpp/algorithm/copy) but there is no analog like _transform_if_.
How it can be trivially implemented shown [here](https://github.com/nikolaAV/skeleton/tree/master/algorithm/transform_if). 
However, it will be good occasion to delve deeper into lambda expressions and implement it by means [lambda currying](../lambda_currying).  
Let's suppose we are going build our own _transform_if_ function which works by supplying [`std::accumulate`](https://en.cppreference.com/w/cpp/algorithm/accumulate) with the right function objects
then our first attempt can be as followed:
```cpp
const auto seq = {1,2,3,4,5,6};
accumulate(begin(seq), end(seq), ostream_iterator<int>(cout,",")
   ,[](auto it, int v){
       if(0==v%2) {               // <-- 1) predicate: even
          const auto res =  2*v;  // <-- 2) action: twice
          *it++ = res;            // <-- 3) accumulation: copy + advance
       }
    return it;
});
// output: 4,8,12 
```
This code can be rewritten in more declarative style:
```cpp
accumulate(begin(seq), end(seq), ostream_iterator<int>(cout,",")
         ,filter(even)(twice)(copy_and_advance)
      );
```
where
```cpp
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
```

## Further informations
* [Currying](https://en.wikipedia.org/wiki/Currying) on Wikipedia
* [zero-overhead C++17 currying](https://vittorioromeo.info/index/blog/cpp17_curry.html) by Vittorio Romeo

## Related links
* [lamda_currying. example 1](../lambda_currying)
* [transform_if](https://github.com/nikolaAV/skeleton/tree/master/algorithm/transform_if)

## Compilers
* [GCC 8.1.0](https://wandbox.org/)
* [clang 6.0.0](https://wandbox.org/)
* Microsoft (R) C/C++ Compiler 19.14 
