#include <iostream>
#include <tuple>

// @brief Pulling a single item from a C++ parameter pack by its index
// @see https://devblogs.microsoft.com/oldnewthing/20240516-00/?p=109771

template <std::size_t Index, typename... Ts>
decltype(auto) get(Ts&&... ts)
{
   return std::get<Index>(std::forward_as_tuple(std::forward<Ts>(ts)...));
}

int main()
{
   std::cout << "The first item is: "  << get<0>(42, 3.14, "Hello") << std::endl;
   std::cout << "The second item is: " << get<1>(42, 3.14, "Hello") << std::endl;
   std::cout << "The third item is: "  << get<2>(42, 3.14, "Hello") << std::endl;
}
