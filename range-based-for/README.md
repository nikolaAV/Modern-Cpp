# range-based for
The following [example](https://github.com/nikolaAV/Modern-Cpp/blob/master/range-based-for/my_own_collection.cpp) illustrates how your own collection classes can be written in order to work together with C++11 feature a.k.a. ['range-based for'](http://en.cppreference.com/w/cpp/language/range-for) (i.e. foreach style) for loops
```cpp
   /**
      Approach 1. Member functions
   */
   template <typename T>
   struct my_container_1
   {
      ...
      const_iterator begin()  const {...}
      const_iterator end()    const {...}
      iterator begin()              {...}
      iterator end()                {...}
   };

   /**
      Approach 2. Free-standign functions
   */
   template <typename T>
   struct my_container_2
   {
      ...
   };

   template <typename T> iterator begin(my_container<T>& c)         {...}
   template <typename T> iterator end(my_container<T>& c)           {... }
   template <typename T> const_iterator begin(const my_container<T>& c)   {...}
   template <typename T> const_iterator end(const my_container<T>& c)     {...}

   // Usage:
   int main()
   {
        my_container_1 c1 = {1,2,3,4,5};
        for (auto v:c1) ...;
        my_container_2 c2 = {6,7,8,9,0};
        for (auto v:c2) ...;
```

# range-based for in reversed direction

Example of an implementation of a reversing container adapter like [boost\::adaptor\::reverse](https://www.boost.org/doc/libs/1_56_0/libs/range/doc/html/range/reference/adaptors/reference/reversed.html#range.reference.adaptors.reference.reversed.reversed_example). The key observation is that __ranged-based for-loops__ works by relying on _begin()_ and _end()_ free-standing functions in order to acquire the range's iterators. If we implement our owns we will be able to sumbstitute forward iterators for bacward ones. Thanks to ADL, one doesn't even need to define these custom begin() and end() in the _std::_ namespace.
```cpp
int main()
{
   for(auto val:reversed({1,2,3,4,5,6,7,8,9}))
      cout << val;
}
```

## Further informations
* [Range-based for loop](http://en.cppreference.com/w/cpp/language/range-for) on cppreference.com
* [Using 'range-based for' on your own collection classes](https://mbevin.wordpress.com/2012/11/14/range-based-for/) by Michael Bevin
* [boost\::adaptors\::reverse](https://www.boost.org/doc/libs/1_56_0/libs/range/doc/html/range/reference/adaptors/reference/reversed.html#range.reference.adaptors.reference.reversed.reversed_example)
* [reverse range-based for-loop](https://stackoverflow.com/questions/8542591/c11-reverse-range-based-for-loop) on stackoverflow

## Related links
* TBD

## Compilers
* [GCC 8.1.0](https://wandbox.org/)
* [clang 6.0.0](https://wandbox.org/)
* Microsoft (R) C/C++ Compiler 19.14 
