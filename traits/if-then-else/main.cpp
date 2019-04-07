#include <type_traits>

namespace naive
{

// ERROR: undefined behavior if T is bool or no integral type:
template<typename T>
struct UnsignedT {
   using type = std::conditional_t
      <std::is_integral_v<T> && !std::is_same_v<T,bool>,
         std::make_unsigned_t<T>,
         T
      >;
};

template <typename T>
using Unsigned = typename UnsignedT<T>::type;

} // end of namespace naive

namespace method1
{
   /**
      Additional level of indirection, so that the
      std::conditional arguments are themselves uses of type functions that wrap the result
   */

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
         MakeUnsignedT<T>,
         IdentityT<T>
      >::type;
};

template <typename T>
using Unsigned = typename UnsignedT<T>::type;

};  // end of namespace method1

namespace method2
{
   /**
      the partial specialization of UnsignedT is enabled via a second template parameter 'Enable'
   */

template<typename T, typename Enable=void> // primary template
struct UnsignedT {
   using type = T; 
};

template<typename T> // specialization for integral types except for 'bool'
struct UnsignedT <T, std::enable_if_t<std::is_integral_v<T> && !std::is_same_v<T,bool>>> {
   using type = std::make_unsigned_t<T>;
};

template <typename T>
using Unsigned = typename UnsignedT<T>::type;
}  // end of namespace method2


int main()
{
   using namespace method2;
   static_assert(std::is_same_v<Unsigned<char>,          unsigned char>);
   static_assert(std::is_same_v<Unsigned<volatile int>,  unsigned volatile int>);
   static_assert(std::is_same_v<Unsigned<bool>,          bool>);
   static_assert(std::is_same_v<Unsigned<float>,         float>);
}
