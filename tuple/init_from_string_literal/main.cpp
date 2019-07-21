#include <tuple>

/**
   Declaring Compile-Time std::tuple of characters initialized with pure C string literals

   "Hello, World!" ---> constexpr std::tuple {'H','e','l','l','o',',',' ','W','o','r','l','d','!'}
   
   \see https://github.com/nikolaAV/Modern-Cpp/tree/master/tuple/init_from_string_literal
*/

template <std::size_t... idx>
constexpr auto make_tuple_chars(const char * s, std::index_sequence<idx...>) {
   // https://github.com/nikolaAV/Modern-Cpp/tree/master/variadic/fold_expressions
   return std::make_tuple(s[idx]...);
}

template <std::size_t N>
constexpr auto make_tuple_chars(const char(&s)[N]) {
   // https://github.com/nikolaAV/Modern-Cpp/tree/master/variadic/variadic_indices
   return make_tuple_chars(s,std::make_index_sequence<N>());
}

// Example of usage

#include <iostream>
#include <string>

using namespace std;

template <typename... Ts>
string str_(Ts... ts) {
   const char tmp[] = { ts... };
   return tmp;
}

template <typename... Ts>
string str(const tuple<Ts...>& t) {
   return apply(str_<Ts...>, t);
}

template <typename... Ts>
void print(const tuple<Ts...>& t) {
   /**
      Alternative way how a tuple can be printed
      \see https://github.com/nikolaAV/Modern-Cpp/tree/master/tuple/for-each
   */
   cout << str(t) << endl;
}

int main()
{
   constexpr auto obj = make_tuple_chars("Hello, World!");
   static_assert(14==tuple_size_v<decltype(obj)>);
   static_assert(get<0>(obj)=='H');
   static_assert(get<1>(obj)=='e');
   static_assert(get<2>(obj)=='l');
   static_assert(get<3>(obj)=='l');
   static_assert(get<4>(obj)=='o');
   static_assert(get<5>(obj)==',');
   static_assert(get<6>(obj)==' ');
   static_assert(get<7>(obj)=='W');
   static_assert(get<8>(obj)=='o');
   static_assert(get<9>(obj)=='r');
   static_assert(get<10>(obj)=='l');
   static_assert(get<11>(obj)=='d');
   static_assert(get<12>(obj)=='!');

   print(obj);
}
