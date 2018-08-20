

/**
   If 'Tupl'e contains 'T' type (including const/volatile qualifications),
   provides the member constant value equal to true. Otherwise value is false.

   \see https://stackoverflow.com/questions/25958259/how-do-i-find-out-if-a-tuple-contains-a-type
*/

#include <type_traits>
#include <tuple>

namespace cpp11
{
   template <typename T, typename Tuple>
   struct has_type;

   template <typename T>
   struct has_type<T, std::tuple<>> : std::false_type {};

   template <typename T, typename U, typename... Ts>
   struct has_type<T, std::tuple<U, Ts...>> : has_type<T, std::tuple<Ts...>> {};

   template <typename T, typename... Ts>
   struct has_type<T, std::tuple<T, Ts...>> : std::true_type {};
}  // namespace cpp11

namespace cpp17
{
   template <typename T, typename Tuple>
   struct has_type;

   template <typename T, typename... Us>
   struct has_type<T, std::tuple<Us...>> : std::disjunction<std::is_same<T, Us>...> {};
}  // namespace cpp17


#include <iostream>

void test_cpp11()
{
   using namespace cpp11;
   static_assert(has_type<int, std::tuple<>>::value == false, "test");
   static_assert(has_type<int, std::tuple<int>>::value == true, "test");
   static_assert(has_type<int, std::tuple<float>>::value == false, "test");
   static_assert(has_type<int, std::tuple<float, int>>::value == true, "test");
   static_assert(has_type<int, std::tuple<int, float>>::value == true, "test");
   static_assert(has_type<int, std::tuple<char, float, int>>::value == true, "test");
   static_assert(has_type<int, std::tuple<char, float, bool>>::value == false, "test");
   static_assert(has_type<const int, std::tuple<int>>::value == false, "test"); // we're using is_same so cv matters
   static_assert(has_type<int, std::tuple<const int>>::value == false, "test"); // we're using is_same so cv matters
}

void test_cpp17()
{
   using namespace cpp17;
   static_assert(has_type<int, std::tuple<>>::value == false, "test");
   static_assert(has_type<int, std::tuple<int>>::value == true, "test");
   static_assert(has_type<int, std::tuple<float>>::value == false, "test");
   static_assert(has_type<int, std::tuple<float, int>>::value == true, "test");
   static_assert(has_type<int, std::tuple<int, float>>::value == true, "test");
   static_assert(has_type<int, std::tuple<char, float, int>>::value == true, "test");
   static_assert(has_type<int, std::tuple<char, float, bool>>::value == false, "test");
   static_assert(has_type<const int, std::tuple<int>>::value == false, "test"); // we're using is_same so cv matters
   static_assert(has_type<int, std::tuple<const int>>::value == false, "test"); // we're using is_same so cv matters
}


int main()
{
}


