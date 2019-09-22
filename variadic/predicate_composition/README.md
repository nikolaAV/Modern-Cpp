# Predicate Composition
Compile time predicates like those in [`<type_traits>`](https://en.cppreference.com/w/cpp/types) are often composed to test complex type properties. 
Let's suppose that we need to have a particular type traits called **'Happy'** which is supposed to be used like this: 
```cpp
template <typename T>
inline constexpr bool Happy_v = Happy<T>::value;

static_assert(Happy_v<T>, "Unhappy, I am.");

template <typename T, typename = enable_if<Happy_v<T>>>
void pursuit_of_happyness() {/*...*/}
```
We want **'Happy'** to check the following type requirements:
* it must have default constructor which does not throw an exception.
* it must have copy constructor which does not throw an exception.
* it must be an user-defined type
* and it must not be polymorphic  

Apart from it can already be expressed in C++17 like 
```cpp
template <typename T>
using is_not_polymorphic = std::negation<std::is_polymorphic<T>>;

template<typename T>
inline constexpr bool Happy_v = std::conjunction_v<
    std::is_class<T>
   ,std::is_nothrow_default_constructible<T>
   ,std::is_nothrow_copy_constructible<T>
   ,is_not_polymorphic<T>
>;
```
let's take a few training sessions as if we are asked to write it with by means the older compiler. 

### Traditional First/Rest Recursive Implementation (C++11)
```cpp
template <template <typename...> class... Preds>
struct Compose;

template <template <typename...> class First, template <typename...> class... Rest>
struct Compose<First,Rest...> {
   template <typename T>
   static constexpr auto value() {
      return First<T>::value && Compose<Rest...>::template value<T>();
   }
};

template <>
struct Compose<> {
   template <typename T>
   static constexpr auto value() {
      return true;
   }
};

using Happy = Compose<
    std::is_class
   ,std::is_nothrow_default_constructible
   ,std::is_nothrow_copy_constructible
   ,is_not_polymorphic
>;

template<typename T>
inline constexpr bool Happy_v = Happy::value<T>();
```
### Simplier Non-Recursive Implementation (C++14)
```cpp
template <template <typename...> class... Preds>
struct Compose {
   template <typename T>
   static constexpr auto value() {
      for(auto i: { Preds<T>::value... })
         if(!i) return false;
      return true;
   }
};

using Happy = Compose<
    std::is_class
   ,std::is_nothrow_default_constructible
   ,std::is_nothrow_copy_constructible
   ,is_not_polymorphic
   >;

   template<typename T>
   inline constexpr bool Happy_v = Happy::value<T>();
```
### By means fold expression (C++17)
```cpp
template<typename T, template <typename...> class... Ts>
inline constexpr bool Composer = (...&&Ts<T>::value);

template<typename T>
inline constexpr bool Happy_v = Composer<T,
    std::is_class
   ,std::is_nothrow_default_constructible
   ,std::is_nothrow_copy_constructible
   ,is_not_polymorphic
>;
```

## Further informations
* [Predicate Composition]() by Stephen Dewhurst on CppCon 2017

## Related links
* [contains_any_all_none with fold expressions](./../fold_expressions#container-any-all-none)
* [Jump to variadic section](../)

## Compilers
* [GCC 8.1.0](https://wandbox.org/)
* [clang 7.0.0](https://wandbox.org/)
