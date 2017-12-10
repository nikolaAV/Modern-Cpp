# Adding C++17 structured bindings support to your classes

C++17 adds [structured bindings](https://isocpp.org/files/papers/P0144R1.pdf) for
- tuple-like objects (`std::tuple`, `std::pair`)
- classes where __all__ the non-static member are _public_ or all public-only non-static members are in a single direct base class.   

Any other complex classes need additional code to be decomposed.
All you need to do is tell the compiler 
1) how many variables you want to expose
2) the types of them
3) how to get at the values.

```cpp
class my_type {
    // data ...

public:

// Step 3. Getters for each one
   template <std::size_t N>
   decltype(auto) get() const { ...???
};

namespace std {
    // Step 1. How many elemenys?
    template<>
    class tuple_size<Config>
        : public std::integral_constant<std::size_t, ???> {};

    // Step 2. What is an element type?
    template<std::size_t N>
    class tuple_element<N, Config> {
        public:
        using type = decltype(std::declval<Config>().get<N>());
    };
}

int main()
{
   auto [x,y,z,...] = my_type{...};
```

# Related links
* [Original Article](https://blog.tartanllama.xyz/structured-bindings/) by Simon Brand

## Supported Compilers
* clang 5.0.0
* gcc 7.2.0
