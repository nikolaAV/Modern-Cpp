#include <iostream>
#include <tuple>
#include <string>


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

   template <typename Tag, typename Tuple>
   constexpr auto 
   get(const Tuple& t) noexcept {
      return std::get<Tag>(t).value;
   }

   template <typename Tag, typename Tuple, typename U>
   constexpr typename std::enable_if_t<!has_type_v<Tag,Tuple>,U> 
   get(const Tuple&, const U& def) noexcept {
      return def;
   }

   template <typename Tag, typename Tuple, typename U>
   constexpr typename std::enable_if_t<has_type_v<Tag,Tuple>,decltype(std::declval<Tag>().value)> 
   get(const Tuple& t, const U&) noexcept {
      return nparam::get<Tag>(t);
   }

}  // namespace nparam, named parameter



namespace tag
{
   struct title   { std::string value; };
   struct left    { int value; };
   struct top     { int value; };
   struct width   { int value; };
   struct height  { int value; };
   struct fill    { bool value; };

} // namespace tag

template <typename... Ts>
void draw_rectangle(Ts... ts)
{
   const auto t = std::make_tuple(ts...);
   using namespace tag;
   draw_rectangle(
       nparam::get<title>(t)
      ,nparam::get<left>(t,0)
      ,nparam::get<top>(t,0)
      ,nparam::get<width>(t,10)
      ,nparam::get<height>(t,20)
      ,nparam::get<fill>(t,false)
   );
}

int main()
{
   using namespace tag;
   draw_rectangle(title{"test"},fill{true},height{100});
}
