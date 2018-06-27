# Tuple signature for functions with variadic parameter list
Let's assume we have a function that accepts a variadic parameter list like this: `foo(int,char,double)`. Such function on a client site should be called as
```cpp
    foo(1,'2',3.14);
```
Additionaly, we want to have an alternative approach calling it like this
```cpp
    auto t = tuple{1,'2',3.14}; 
    foo(t);
```
i.e. instead of passing arbitrary sets of arguments we prefer to pass a single tuple containing these arguments.\  
Possible implementation of foo(tuple<...>&&)
```cpp
    template <typename... Ts>
    decltype(auto) foo(std::tuple<Ts...>&& t)
    {
       return
          std::apply(
              [](auto&&... ts){ return foo(std::forward<Ts>(ts)...); }
             ,std::forward<tuple<Ts...>>(t)
          );
    }
```
We first use a lambda expression that arbitrarily accepts many parameters `(auto&&... ts)` and then calls `foo(...)` with variadic parameter list.
On the second, an actual tuple unpacking is done by means [std::apply](https://en.cppreference.com/w/cpp/utility/apply). All values will be taken out of the tuple and then lined up as required in function parameter list.

## Further informations
* [std::apply](https://en.cppreference.com/w/cpp/utility/apply)
* [std::forward](https://en.cppreference.com/w/cpp/utility/forward)

## Related links
* [Universal Delegate (Function Call Wrapper)](../../variadic/universal%20delegate/README.md#callfunctionargs)


## Compilers
* [GCC 8.1.0](https://wandbox.org/)
* [clang 6.0.0](https://wandbox.org/)
* Microsoft (R) C/C++ Compiler 19.14
