# `std::conditional`. "Suppressing" 'false' branch compile time evaluation.
Unlike a normal C++ __if-then-else__ statement, the template arguments for both the “then” and “else” branches are evaluated _before the selection is made_, so neither branch may contain ill-formed code, or the program is likely to be ill-formed.
Let's suppose, it's required to write a trait that yields the corresponding unsigned type for a given signed type. 
There is a standard trait, [`std::make_unsigned`](https://en.cppreference.com/w/cpp/types/make_unsigned), which does this conversion, but it requires that the passed type is a signed integral type and no `bool`; otherwise its use results in undefined behavior. 
So it might be a good idea to implement a trait that yields the corresponding unsigned type if this is possible and the passed type otherwise (thus, avoiding undefined behavior if an inappropriate type is given).  
The naive implementation does not work:
```cpp
template<typename T>
struct UnsignedT {
   using type = std::conditional_t
      <std::is_integral_v<T> && !std::is_same_v<T,bool>,
         std::make_unsigned_t<T>,   // Line A
         T
      >;
};

std::is_same_v<UnsignedT<char>::type, unsigned char>;
std::is_same_v<UnsignedT<bool>::type, bool>;    // <-- Compile Error or BU
```
The instantiation of 'UnsignedT\<bool\>' is still undefined behavior, because the compiler will still attempt to form the type from '`std::make_unsigned_t`\<T\>' (_Line A_).
### Approach A
We need to add an additional level of indirection, so that the `std::conditional` arguments are themselves uses of type functions that wrap the result
```cpp
// yield T when using member Type:
template<typename T>
struct IdentityT {
   using type = T;
};

// to make unsigned after std::conditional was evaluated:
template<typename T>
struct MakeUnsignedT {
   using type = std::make_unsigned_t<T>;
};

template<typename T>
struct UnsignedT {
   using type = typename std::conditional_t
      <std::is_integral_v<T> && !std::is_same_v<T,bool>,
         MakeUnsignedT<T>,  // function type wrapper for std::make_unsigned_t
         IdentityT<T>       // function type wrapper for pure T
      >::type;              // <-- a real evaluation is here
};
```
In this definition of 'UnsignedT', the type arguments to `std::conditional` are both instances of type functions themselves. 
However, __the type functions are not actually evaluated__ before `std::conditional` selects one. 
Instead, `std::conditional` selects the type function instance (of either 'MakeUnsignedT' or 'IdentityT'). 
The '::type' then evaluates the selected type function instance to produce 'type'.
### Approach B
The second approach to implement [SFINAE](https://en.cppreference.com/w/cpp/language/sfinae)-based traits uses partial specialization.
We can use it to find out whether a type T meets the criteria: "it's a integral type and not `bool`". 
`std::conditional` is no longer needed.
```cpp
template<typename T, typename Enable=void> // primary template
struct UnsignedT {
   using type = T; 
};

template<typename T> // specialization for integral types except for 'bool'
struct UnsignedT <T, std::enable_if_t<std::is_integral_v<T> && !std::is_same_v<T,bool>>> {
   using type = std::make_unsigned_t<T>;
};
```
We define the general case (primary template) for any T returning T itself.
The second template argument 'Enable' that defaults to the type of a helper `void`. 
It enables us to provide partial specializations that use an compile-time type constructs defining the criteria: "it's a integral type and not `bool`". 
In this case, we need only one construct
```cpp
std::enable_if_t<std::is_integral_v<T> && !std::is_same_v<T,bool>>
```
to check again whether T meets the criteria.
If, for a specific T, the construct is invalid, SFINAE this time causes the whole partial specialization to be discarded, and we fall back to the primary template. 
Otherwise, the partial specialization is valid and preferred.
## Further informations
* [`std::make_unsigned`](https://en.cppreference.com/w/cpp/types/make_unsigned)
* [`std::conditional`](https://en.cppreference.com/w/cpp/types/conditional)
* [SFINAE](https://en.cppreference.com/w/cpp/language/sfinae)
* [`std::enable_if`](https://en.cppreference.com/w/cpp/types/enable_if)
* [std::conditional compile-time branch evaluation](https://stackoverflow.com/questions/24098278/stdconditional-compile-time-branch-evaluation) on stackoverflow
* [C++ Templates: The Complete Guide (2nd Edition)](http://www.tmplbook.com/) by David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. Chapter 19.7.1
## Related links
* [iterator_type_traits](https://github.com/nikolaAV/skeleton/tree/master/iterator_traits2)

## Compilers
* [GCC 8.1.0](https://wandbox.org/)
* [clang 6.0.0](https://wandbox.org/)
* Microsoft (R) C/C++ Compiler 19.14 
