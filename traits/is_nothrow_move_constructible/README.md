# 'is_nothrow_move_constructible' trait by our own hands.
There has already been the [`std::is_nothrow_move_constructible`](https://en.cppreference.com/w/cpp/types/is_move_constructible) trait since `C++11`. 
So let's suppose we need to get experience writing type trait. We need to obtain information about techniques / practices hoe it can be done in the Modern `C++`.  
### Motivation
If you design generic code (i.e. a library) that depends on types specified by a client you may often have to detect what facilities a clien type provides. 
It is occasionally useful to determine whether a particular operation can throw an exception. 
For example, a move constructor should be marked `noexcept`, indicating that it does not throw exceptions, whenever possible. 
However, whether a move constructor for a particular class throws exceptions or not often depends on whether the move constructors of its members and bases throw. 
For example, your generic type, you are working out, is similar to [`std::pair`](https://en.cppreference.com/w/cpp/utility/pair).
```cpp
template <typename T1, typename T2>
struct pair {
   T1 first;
   T2 second;

   pair(pair&& other) noexcept (is_nothrow_move_constructible_v<T1> && is_nothrow_move_constructible_v<T2>)
      :   first(std::forward<T1>(other.first))
         ,second(std::forward<T2>(other.second))
   {}
// ...
```
__pair__’s move constructor can throw exceptions when the move operations of either T1 or T2 can throw. 
Given a trait __'is_nothrow_move_constructible'__, we can express this property by using a computed `noexcept` exception specification in __pair__’s move constructor.  
### Implementation
All that remains is to implement the __'is_nothrow_move_constructible'__ trait. 
We can directly implement this trait using the `noexcept` operator, which determines whether a given expression is guaranteed to be nonthrowing.
```cpp
template<typename T>
struct is_nothrow_move_constructible
: std::bool_constant<noexcept(T(std::declval<T>()))>
{};
```
However, this implementation should be improved because it is not [SFINAE-friendly](http://kaba.hilvi.org/pastel-1.5.0/sfinae_friendliness.htm). 
If the trait is instantiated with a type __T__that does not have a usable move or copy constructor—making the expression `T(std::declval<T&&>())` invalid — the entire program is ill-formed:
```cpp
struct no_copy {  // non copyable
    no_copy(const no_copy&) = delete;
};
...
std::cout << is_nothrow_move_constructible<no_copy>::value; // compile-time ERROR
```
Instead of aborting the compilation, the type trait should yield a `value` of `false`. 
We have to check whether the expression computing the result is valid before it is evaluated. 
Here, we have to find out whether move construction is valid before checking whether it is `noexcept`.
Thus, we revise the first version of the trait by adding a template parameter that defaults to `void` and a partial that uses [`std::void_t`](https://en.cppreference.com/w/cpp/types/void_t) for that parameter with an argument that is valid only if move construction is valid:
```cpp
template <typename T, typename = std::void_t<>>
struct is_nothrow_move_constructible 
   : std::false_type {
};

template <typename T>
struct is_nothrow_move_constructible <T,std::void_t<decltype(T(std::declval<T>()))>> 
   : std::integral_constant<bool,noexcept(T(std::declval<T>()))> {
};
```
If the substitution of `std::void_t<…>` in the partial specialization is valid, that specialization is selected, and the `noexcept(…)` expression in the base class specifier can safely be evaluated. 
Otherwise, the partial specialization is discarded
without instantiating it, and the primary template is instantiated instead producing a `std::false_type` result.  
Note that there is no way to check whether a move constructor throws without being able to call it directly. 
That is, it is not enough that the move constructor is public and not deleted, it also requires that the corresponding type is no abstract class (references or pointers to abstract classes work fine).

## Further informations
* [`std::is_nothrow_move_constructible`](https://en.cppreference.com/w/cpp/types/is_move_constructible)
* [SFINAE](https://en.cppreference.com/w/cpp/language/sfinae)
* [C++ Templates: The Complete Guide (2nd Edition)](http://www.tmplbook.com/) by David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. Chapter 19.7.2
* [Notes on C++ SFINAE](https://www.bfilipek.com/2016/02/notes-on-c-sfinae.html), [SFINAE Followup](https://www.bfilipek.com/2016/02/sfinae-followup.html) by Bartlomiej Filipek
* [SFINAE friendliness](http://kaba.hilvi.org/pastel-1.5.0/sfinae_friendliness.htm)

## Related links
* [Detection Idiom](../../concept%20(pceudo)/detection_idiom)
* [has_member](../../concept%20(pceudo)/has_type_member)

## Compilers
* [GCC 8.1.0](https://wandbox.org/)
* [clang 6.0.1](https://wandbox.org/)
* Microsoft (R) C/C++ Compiler 19.14 
