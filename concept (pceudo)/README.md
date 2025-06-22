# C++ concept ([Concepts Lite](https://isocpp.org/blog/2013/02/concepts-lite-constraining-templates-with-predicates-andrew-sutton-bjarne-s))
A few alternative routes before C++20 supports [them](http://en.cppreference.com/w/cpp/language/constraints)

## "Why are concepts needed?" kick off.
Let's suppose we have just finished writing 'sum' function for two [`std::optional`](https://en.cppreference.com/w/cpp/utility/optional) values. While it’s unusual to overload operators for standard types, in common sense it may be warranted since there is a [similar abstractions](https://wiki.haskell.org/Maybe) that other languages have and could have applications in other code bases.  
```cpp
template <typename T>
auto operator+(const std::optional<T>& left, const std::optional<T>& right) {
   if(left && right)
      return std::make_optional(*left +*right); // Line A
   return left? left : right; 
}
```
As a templated function, this allows us to combine any two optionals so long as the value inside it has an __operator+__ defined for it. If not you’ll get an error at line _Line A_. Below a code couses it:  
```cpp
struct widget{};
auto w1 = std::make_optional<widget>();
auto w2 = std::make_optional<widget>();
auto w3 = w1 + w2; // <--- the error comes up from body operator+ during its instantiation.   
```
Just to make our intention clear and specify exactly what is required for type T, `C++20` gives us _concepts_.
```cpp
template<typename T>
concept Magma = requires(T a)
{
    { a + a } -> T; // a binary operator that returns the same Type
    // define operator+ for your Type if you get an error here
};

template <Magma T>
auto operator+(const std::optional<T>& left, const std::optional<T>& right) {
   // ...
```
Compiling with -c++=2a and -fconcepts we still get some diagnostics about operator+, but we also get a new one:
```
note:   constraints not satisfied
note: within 'template<class T> concept const bool Magma<T> [with T = widget
14 | concept Magma= requires(T a)
|         ^~~~~~~~~
note: with 'widget
note: the required expression '(a + a)' would be ill-formed
```
_A concept_ at least gives you a chance to write language constructs in the code that can give better direction to the user.  
Is there a way to use _concepts_ in compilers that do not support them?
Here is an example of [one of possibility](../stl/optional/main3.cpp):
```cpp
namespace concepts {

   template <typename T, typename = void>
   struct is_addition_supported : std::false_type {};

   template <typename T>
   struct is_addition_supported<T, std::void_t<decltype(std::declval<T>() + std::declval<T>())>>
                                : std::true_type {};
   template<typename T>
   inline constexpr bool is_addition_supported_v = is_addition_supported<T>::value;

} // end namespace concepts

auto operator+(const std::optional<T>& left, const std::optional<T>& right) {
   static_assert(concepts::is_addition_supported_v<T>, "no match for T+T");
   // ...
```

## Further informations
* using `std::enable_if`, for more details see [the article](https://habrahabr.ru/post/304728/)
* using wrappers that are implemented by means C++ structures with concept-specified interface as [function-members set](https://habrahabr.ru/post/151504/)
* [How to Make SFINAE Pretty](https://www.fluentcpp.com/2018/05/18/make-sfinae-pretty-2-hidden-beauty-sfinae/)
* [Detection Idiom - A Stopgap for Concepts](https://blog.tartanllama.xyz/detection-idiom/) by Simon Brand
* [Notes on C++ SFINAE](https://www.bfilipek.com/2016/02/notes-on-c-sfinae.html), [SFINAE Followup](https://www.bfilipek.com/2016/02/sfinae-followup.html) by Bartlomiej Filipek

## Related links
* Example of an approach based on `std::enable_if` to make set of overloaded [XOR cipher algorithm](https://github.com/nikolaAV/skeleton/blob/master/algorithm/simple_xor).
* [Example](./enable_if_ctor) how to disable partially member function templates.
* `static_assert` is another mechanism to specify sort of types allowed as input parameter in [insert_sorted algorithm](https://github.com/nikolaAV/skeleton/tree/master/algorithm/insert_sorted) or [Fizz buzz game implemented with `std::optional`](../stl/optional/)
* [new facilities coming with C++20](../concept%20(C++20)) 
