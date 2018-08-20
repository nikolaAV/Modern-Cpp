# Compile-time check of a requested type in the tuple.  
```cpp
   static_assert(has_type<int, std::tuple<>>::value == false, "test");
   static_assert(has_type<int, std::tuple<int>>::value == true, "test");
   static_assert(has_type<int, std::tuple<float>>::value == false, "test");
   static_assert(has_type<int, std::tuple<float, int>>::value == true, "test");
   static_assert(has_type<int, std::tuple<int, float>>::value == true, "test");
   static_assert(has_type<int, std::tuple<char, float, int>>::value == true, "test");
   static_assert(has_type<int, std::tuple<char, float, bool>>::value == false, "test");
   static_assert(has_type<const int, std::tuple<int>>::value == false, "test"); // we're using is_same so cv matters
   static_assert(has_type<int, std::tuple<const int>>::value == false, "test"); // we're using is_same so cv matters
```

## Further informations
* [How do I find out if a tuple contains a type?](https://stackoverflow.com/questions/25958259/how-do-i-find-out-if-a-tuple-contains-a-type)
## Related links
* [Named parameters for functions in C++14](../named_params)
## Compilers
* [GCC 8.1.0](https://wandbox.org/)
* [clang 6.0.0](https://wandbox.org/)
* Visual C++ 19.14 
