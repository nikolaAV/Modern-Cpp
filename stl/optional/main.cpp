#include <optional>
#include <utility>
#include <type_traits>
#include <iterator>

/**
	Handy extension to std::map. (generally, any container holding elements of type std::pair<T,U>)
	Rather than checking for map::end you can use std::optional.

	\see https://www.bfilipek.com/2018/06/optional-examples-wall.html
	     https://github.com/nikolaAV/Modern-Cpp/tree/master/stl/optional#example-1-cleaner-interface-for-associative_containerfind
*/

namespace concepts
{  // https://github.com/nikolaAV/Modern-Cpp/tree/master/concept%20(pceudo)/has_type_member
    
   template <typename ContainerT, typename KeyT, typename = void>
   struct has_member_find : std::false_type {};

   template <typename ContainerT, typename KeyT>
   struct has_member_find<ContainerT, KeyT, std::void_t<decltype(std::declval<ContainerT>().find(std::declval<KeyT>()))>> : std::true_type {};

   template <typename ContainerT, typename KeyT>
   constexpr inline bool has_member_find_v = has_member_find<ContainerT, KeyT>::value;

   template <typename IteratorT>
   using iterator_value = typename std::iterator_traits<IteratorT>::value_type;

   template <typename IteratorT, typename = void>
   struct is_pair_iterator : std::false_type {};

   template <typename IteratorT>
   struct is_pair_iterator<IteratorT,std::void_t<decltype(std::declval<iterator_value<IteratorT>>().first), decltype(std::declval<iterator_value<IteratorT>>().second)>> : std::true_type {};

   template <typename IteratorT>
   constexpr inline bool is_pair_iterator_v = is_pair_iterator<IteratorT>::value;
} // end of namespace concepts


template <typename IterT>
struct optinal_pair_iterator : std::optional<IterT> {
   using base_type  = std::optional<IterT>;
   using base_type::base_type;
   constexpr auto&         operator*() &        { return this->value()->second; }
   constexpr auto&&        operator*() &&       { return this->value()->second; }
   constexpr const auto&   operator*() const&   { return this->value()->second; }
   constexpr const auto&&  operator*() const&&  { return this->value()->second; }
};

template <typename ContainerT, typename KeyT>
auto lookup(ContainerT& c, KeyT&& k) {
   static_assert(concepts::has_member_find_v<ContainerT,KeyT>,"function member 'find' is expected");
   auto it = c.find(std::forward<KeyT>(k));
   static_assert(concepts::is_pair_iterator_v<decltype(it)>,"iterator to a pair is expected");
   using return_type = optinal_pair_iterator<decltype(it)>;
   return it!=std::end(c)? return_type{it} : return_type{};
}

#include <iostream>
#include <map>
#include <string>
#include <cassert>
#include <unordered_map>

using namespace std;

const map<int, string>         digits{ {1,"one"},{2,"two"},{3,"three"},{4,"four"} };
unordered_map <string, double> prices{ {"oranges",1.}, {"apples",2.}, {"cherries",3.}, {"pears", 4.}, {"peaches",5.} };


int main()
{
   assert("two" == *lookup(digits, 2));
   assert("two" != *lookup(digits, 1));
   assert(!lookup(digits, 5));

   *lookup(prices, "cherries") = 0.5;
   assert(.5 == *lookup(prices, "cherries"));

/*
   if(auto it = digits.find(2); it != digits.end())
      cout << "digit is " << (*it).second << endl;
   else
      cout << "unknown digit" << endl;

   if (auto digit = lookup(digits,2))
      cout << "digit is " << *digit << endl;
   else
      cout << "unknown digit" << endl;

   if (auto product = lookup(prices,"apples"))
      *product =3.14;
*/
}
