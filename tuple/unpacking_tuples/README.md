# Unpacking & enumerating Tuples in C++14
Some useful primitives to deal with tuples in generic fashion.

### decltype(auto) take_front<N>(Tuple&& t)
takes an arbitrary tuple and returns a new tuple that holds the first N elements of the original tuple
```cpp
   auto t = take_front<2>(std::make_tuple(1, 2, 3, 4));
   assert(t == std::make_tuple(1, 2));
```

### decltype(auto) take_back<N>(Tuple&& t)
takes an arbitrary tuple and returns a new tuple that holds the last N elements of the original tuple in reversed ordering
```cpp
   auto t = take_back<2>(std::make_tuple(1, 2, 3, 4));
   assert(t == std::make_tuple(4, 3));
```

### decltype(auto) reverse(Tuple&& t)
takes a tuple and returns a new tuple that contains the original tuple’s elements in reversed order
```cpp
   auto t = treverse(std::make_tuple(1, 2, 3, 4));
   assert(t == std::make_tuple(4, 3, 2, 1));
```

### decltype(auto) apply(F&& f, Tuple&& t)
takes a callable (f) and a tuple (t) and calls the callable with the elements of the tuple as arguments
```cpp
   int sum(int a0, int a1, int a2, int a3)
   {
      return  a0 + a1 + a2 + a3;
   }
   auto t = apply(sum,std::make_tuple(1, 2, 3, 4));
   assert(10 == t);
```

### decltype(auto) for_each(F&& f, Tuple&& t)
takes a callable (f) and a tuple (t) and calls the callable with the each element in a row in ordering elements of the tuple
```cpp
   struct sum
   {
      int value = 0;
      void operator()(int v) { value += v; }
   };
   auto t = for_each(sum3{},std::make_tuple(1, 2, 3, 4));
   assert(10 == t.value);
```

### How to pass various number of arguments of any type into a lambda
```cpp
template <typename Function, typename... Args>
inline 
decltype(auto)
delegate_call(Function&& f, Args&&... args)
{
   // lambda signatute: T(void)
   auto lambda = [f=forward<Function>(f),a=std::make_tuple(std::forward<Args>(args)...)]() { 
      return tu::apply(std::move(f),std::move(a));
   };
   // this lambda can be moved into suitable place where it can be triggered later
   // ...
   return lambda();
}
```
* Let's suppose there is a function with signatute: T **fn**(Arg1,Arg2,...)
* we need to delegate it for further invocation: T delegate(**fn**,Arg1,Arg2,...)
* so, we pack input arguments (Arg1,Arg2,...) into a singular object of `std::tuple`<Arg1,Arg2,...> type
* create a lambda expression ( signature -> T( **void** ) ) which
    * captures the input argument pack (`std::tuple`) by means **moving(!!!)**
    * in lambda's body, we unpack this pack (`std::tuple`) back
    * call the original **fn**
    * and return the value returned by the **fn**

Example of usage:
```cpp
auto foo(int& v1, int& v2) 
{
   const auto r = make_pair(v1,v2);
   v1 = v2 = 0;
   return r;
}

int v1{1}, v2{2};
auto ret = delegate_call(foo2,ref(v1),ref(v2));
assert(1==ret.first && 2==ret.second);
assert(0==v1 && 0==v2);
```

## Further informations
* [Unpacking Tuples in C++14](http://aherrmann.github.io/programming/2016/02/28/unpacking-tuples-in-cpp14/) by Andreas Herrmann
* [std::apply, since C++17](http://en.cppreference.com/w/cpp/utility/apply) 
* [How can I iterate over a tuple](https://stackoverflow.com/questions/1198260/iterate-over-tuple) on stackoverflow.com

## Related links
* [Enumerating elements of different types in a heterogeneous container (C++17)](https://github.com/nikolaAV/Modern-Cpp/tree/master/variant/heterogeneous_container) by nikolaAV on GitHub

## Supported Compilers
* Microsoft (R) C/C++ Optimizing Compiler Version 19.10.xyz ([Visual Studio 2017](https://www.visualstudio.com/vs/visual-studio-express/))
