# C++ Detection Idiom. Modern way (since C++17)
The detection idiom is what allows compile-time type introspection in C++. 
Using the detection idiom, we can check if a type has methods, type aliases, or members that fit a particular interface. 
This allows library writers to create metaprogramming facilities that are much more expressive. 
The user can plug any type she or he likes into a metafunction as long as it fits the required interface.  
C++ 20 will have a first-class facility for compile-type type introspection called [concepts](https://accu.org/index.php/journals/2157). 
Concepts are more concise and explicit than current iterations of the detection idiom and will result in better compiler errors. 
For now, though, we emulate concepts using the [detection idiom](https://blog.tartanllama.xyz/detection-idiom/).  
Let's suppose we want to make annoying signatures of stl iterator based algorithms more expressive and shorter.
```cpp
   const auto seq1 = {0,1,2,3,4,5,6,7,8,9};
   const auto seq2 = std::vector{0,1,2,3,4,5,6,7,8,9};
   const auto seq3 = std::set{0,1,2,3,4,5,6,7,8,9};

   // instead of writing lines like that
   assert(45 == std::accumulate(std::begin(seq1),std::end(seq1),0));
   assert(45 == std::accumulate(std::begin(seq2),std::end(seq2),0));
   assert(45 == std::accumulate(std::begin(seq3),std::end(seq3),0));
   // it would be rather more expressive if we are able to rewrite them like
   assert(45 == accumulate(seq1,0));
   assert(45 == accumulate(seq2,0));
   assert(45 == accumulate(seq3,0));
```
To do that we have to provide our own signature of the algorithm which accepts a parameter of 'Container' type. 
First attempt may be shown as:
```cpp
template< typename Container, typename T>
T accumulate( const Container& c, T init) {
   return std::accumulate(std::begin(c),std::end(c),init);
}
```
It works but the interface of the given algorithm is too much generic as it is required. 
From that comes the term _unbounded polymorphism_ that means the interface of the type (__typename Container__) participating in function declaration is not predetermined. 
In order to specify what requirements __Container__ type must meet we may express it directly in the code like that (before concepts in C++ will have been supported)
```cpp
template< typename Container, typename T>
T accumulate( const Container& c, T init) {
   static_assert(is_range_v<Container>);
   return std::accumulate(std::begin(c),std::end(c),init);
}
```
where 'is_range_v' is a compile time trait which says whether the specified type T can be represented by pair of iterators pointing out the begining/the end of element sequence. 
According to the Detection Idiom, the mentioned trait may be implemented like that
```cpp
template <typename T> 
using begin_t  = decltype(std::begin(std::declval<T>()));
template <typename T> 
using end_t    = decltype(std::end(std::declval<T>()));
template <typename T> 
inline constexpr bool is_range_v = std::experimental::is_detected_v<begin_t,T> 
                                && std::experimental::is_detected_v<end_t,T>;
```

## Further informations
* [C++ Detection Idiom Through the Years](https://people.eecs.berkeley.edu/~brock/blog/detection_idiom.php)
* [Detection Idiom - A Stopgap for Concepts](https://blog.tartanllama.xyz/detection-idiom/)
* [`std::experimental::is_detected`](https://en.cppreference.com/w/cpp/experimental/is_detected) 
## Related links
* [iterator_type_traits](https://github.com/nikolaAV/skeleton/tree/master/iterator_traits2)
* [algorithm 'XOR cipher'. how to make overloads](https://github.com/nikolaAV/skeleton/tree/master/algorithm/simple_xor)
* [how to detect overloads](../../traits/custom_safe_fallback)
## Compilers
* [GCC 8.1.0](https://wandbox.org/)
* [clang 7.0.0](https://wandbox.org/)
* Microsoft (R) C/C++ Compiler 19.14 
