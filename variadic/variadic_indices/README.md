# Variadic Indices
The following function uses a variadic list of indices to access the corresponding element of the passed first argument:
```cpp
template<typename C, typename… Idx>
void print(C const& coll, Idx… idx){
    ((std::cout << coll[idx]),...);
}
```
That is, when calling
```cpp
std::vector<std::string> coll = {" good", " times", " say", " bye"};
print(coll,2,0,3);
```
the effect is to call
```cpp
std::cout << c[2],std::cout << c[0],std::cout << c[3];
\\ output: say good bye
```
You can also declare nontype template parameters to be parameter packs. For example:
```cpp
template<std::size_t… Idx, typename C>
void print (C const& coll) {
    ((std::cout << c[Idx]),...);
}
```
allows you to call
```cpp
print<2,0,3>(coll);
```
You can also define a class that _as a type_ represents a list of indices:
```cpp
template<std::size_t…> struct indices {};
```
This can be used to define a function that calls expression _std\::cout << std\::get\<Idx\>(c)_ for the elements of a `std::array` or `std::tuple` using the compile-time access with `std::get<>()` for the given indices:
```cpp
template<typename C, size_t... Idx>
void print(const C& c, indices<Idx...>) {
    ((std::cout << std::get<Idx>(c)),...);
}
```
This template can be used as follows:
```cpp
std::array<std::string,4> coll = {" good", " times", " say", " bye"};
print(coll,indices<2,0,3>{});
```
And finaly you can use `std::index_sequence` object to print first __N__ elements:
```cpp
template<typename C, size_t... Idx>
void print(const C& c, std::index_sequence<Idx...>) {
    ((std::cout << std::get<Idx>(c)),...);
}
// usage:
print(coll,std::make_index_sequence<4>{});
// output: good times say bye
```

## Further informations
* [C++ Templates - The Complete Guide, 2nd Edition](http://www.tmplbook.com/)by David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor, chapter 21.3
* [std::index_sequence](https://en.cppreference.com/w/cpp/utility/integer_sequence) 
## Related links
* [parameter pack enumeration](../enumeration#enumeration-of-elements-in-the--expression)
* [fold expressions](../fold_expressions)
* [Indices for compile time C-arrays. Usage example: gcd](../../constexpr/greatest_common_divisor)
* [back to 'variadic' section](../)
## Compilers
* [GCC 7.1.0](https://wandbox.org/)
* [clang 6.0.0](https://wandbox.org/)
* Visual C++ 19.14 
