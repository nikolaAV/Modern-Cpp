#include <type_traits>
#include <utility>

/**
   \see https://github.com/nikolaAV/Modern-Cpp/tree/master/traits/is_nothrow_move_constructible
*/

template <typename T, typename = std::void_t<>>
struct is_nothrow_move_constructible 
   : std::false_type {
};

template <typename T>
struct is_nothrow_move_constructible < T,
            std::void_t<decltype(T(std::declval<T>()))> // https://github.com/nikolaAV/Modern-Cpp/tree/master/concept%20(pceudo)/detection_idiom
         > 
   : std::integral_constant<bool,noexcept(T(std::declval<T>()))> {
};

template <typename T>
inline constexpr bool is_nothrow_move_constructible_v = is_nothrow_move_constructible<T>::value;
 
//// Usage
#include <string>

template <typename T1, typename T2>
struct pair {
   T1 first;
   T2 second;

   pair(pair&& other) noexcept (is_nothrow_move_constructible_v<T1> && is_nothrow_move_constructible_v<T2>)
      :   first(std::forward<T1>(other.first))
         ,second(std::forward<T2>(other.second))
   {}
};

struct can_throw {
    can_throw(can_throw&&) {}
};

struct no_move {  // has no move ctor
    // https://en.cppreference.com/w/cpp/types/is_move_constructible
    // prevents implicit declaration of default move constructor
    // however, the class is still move-constructible because its
    // copy constructor can bind to an rvalue argument
    no_move(const no_move&) {}
};

struct no_copy {  // non copyable
    no_copy(const no_copy&) = delete;
};

int main()
{
   static_assert( is_nothrow_move_constructible_v<std::string>);
   static_assert(!is_nothrow_move_constructible_v<can_throw>);
   static_assert(!is_nothrow_move_constructible_v<no_move>);
   static_assert(!is_nothrow_move_constructible_v<no_copy>);

   static_assert( is_nothrow_move_constructible_v<pair<std::string,std::string>>);
   static_assert(!is_nothrow_move_constructible_v<pair<no_move,std::string>>);
   static_assert(!is_nothrow_move_constructible_v<pair<std::string,no_copy>>);
   static_assert(!is_nothrow_move_constructible_v<pair<can_throw,can_throw>>);
}

