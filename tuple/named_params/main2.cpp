#include <iostream>
#include <tuple>
#include <string>

/**
   The implementation of the named parameters. Variant 2
   Default values are specified in each separate value type:
   --------------------------------------------------------

   T0 given_function(T1 a1=A1, T2 a2=A2, T3 a3=A2) {...} // <-- from third-party library
   can be rewritten as:

   struct typeT1 { T1 value = A1; }                   // <--- The default value is singled out here! 
   struct typeT2 { T2 value = A2; }
   struct typeT3 { T3 value = A3; }

   template <typename... Ts>
   auto given_function(Ts... ts) {                    // <--- the wrapper function
      const auto t = std::make_tuple(ts...);
      return given_function(
          nparam::get<typeT1>(t)
         ,nparam::get<typeT2>(t)
         ,nparam::get<typeT3>(t)
      ); 
   }

   \see Variant 1, where the default params specified in the wrapper function

*/


void draw_rectangle(const std::string& title, int left=0, int top=0, int width=10, int height=20, bool fill = false)
{
   using namespace std;
   cout << "title: "    << title                     << "\n"
        << "left: "     << left                      << "\n"
        << "top: "      << top                       << "\n"
        << "width: "    << width                     << "\n"
        << "height: "   << height                    << "\n"
        << "fill: "     << boolalpha << fill         << "\n";
}

///////////////

/**
   https://isocpp.org/blog/2014/12/named-parameters-in-modern-cpp
   http://www.open-std.org/JTC1/SC22/WG21/docs/papers/2014/n4172.htm
   https://www.numbercrunch.de/blog/2015/11/revisiting-the-named-parameter-idiom-in-c14/
*/

namespace nparam  // named paremeter
{
   template <typename T, typename Tuple>
   struct has_type;

   template <typename T, typename... Us>
   struct has_type<T, std::tuple<Us...>> : std::disjunction<std::is_same<T, Us>...> {};

   template <typename T, typename Tuple>
   inline constexpr bool has_type_v = has_type<T, Tuple>::value;

   /**
      returns a desired function argument from the tuple or a possible default value if not present.
   */

   template <typename Tag, typename Tuple>
   constexpr typename std::enable_if_t<!has_type_v<Tag,Tuple>,decltype(std::declval<Tag>().value)>
   get(const Tuple&) noexcept {
      return Tag{}.value;
   }

   template <typename Tag, typename Tuple>
   constexpr typename std::enable_if_t<has_type_v<Tag,Tuple>,decltype(std::declval<Tag>().value)>
   get(const Tuple& t) noexcept {
      return std::get<Tag>(t).value;;
   }

}  // end namespace nparam


namespace tag
{
   struct title   { std::string value; };
   struct left    { int value{0}; };
   struct top     { int value{0}; };
   struct width   { int value{10}; };
   struct height  { int value{20}; };
   struct fill    { bool value{false}; };

} // namespace tag

template <typename... Ts>
void draw_rectangle(Ts... ts)
{
   const auto t = std::make_tuple(ts...);
   using namespace tag;
   draw_rectangle(
       nparam::get<title>(t)
      ,nparam::get<left>(t)
      ,nparam::get<top>(t)
      ,nparam::get<width>(t)
      ,nparam::get<height>(t)
      ,nparam::get<fill>(t)
   );
}

int main()
{
   using namespace tag;
   draw_rectangle(title{"test"},fill{true},height{100});
}
