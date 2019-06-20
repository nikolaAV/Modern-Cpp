#include <iostream>
#include <string>
#include <sstream>
#include <string_view>
#include <vector>
#include <tuple>
#include <utility>

using namespace std;

/**
   https://blog.tartanllama.xyz/structured-bindings/

   Adding C++17 structured bindings support to your classes

   \note: Code below is only compilable under clang 5.0.0 and gcc 7.2.0
          Visual C++ 19.12.xx raises an error: "C2440: 'initializing': cannot convert from '::size_t' to 'size_t &'" al Line A
*/

class Config {
    std::string name = "user-defined structured bindings";
    std::size_t id   = 17;
    std::vector<std::string> data;

    //constructors and such

public:

// Step 2. Getter for each one
   template <std::size_t N>
   decltype(auto) get() const {
       if      constexpr (N == 0) return std::string_view{name};
       else if constexpr (N == 1) return id;
       else if constexpr (N == 2) return (data); //parens needed to get reference
   }
};

// Step 1. How many elemenys? there are three 
namespace std {
    template<>
    class tuple_size<Config>
        : public std::integral_constant<std::size_t, 3> {};
}

// Step 3. What is an element type? 
namespace std {
    template<std::size_t N>
    class tuple_element<N, Config> {
        public:
        using type = decltype(std::declval<Config>().get<N>());
    };
}

Config get_config()
{
   return Config{}; 
}

int main()
{
   auto [name, id, data] = get_config();

   cout << name << " " << id << endl;  // <- Line A
}
     