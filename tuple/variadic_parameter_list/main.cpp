#include <iostream>
#include <tuple>
#include <utility>

// variadic version
template <typename... Ts>
bool print(Ts&&... ts)
{
   using namespace std; 
   ((cout << forward<Ts>(ts) << " "),...);   
   cout << endl;
   return true;
}

// tupe verson
template <typename... Ts>
decltype(auto) print(std::tuple<Ts...>&& t)
{
   return
      std::apply(
          [](auto&&... ts){ return print(std::forward<Ts>(ts)...); }
         ,std::forward<std::tuple<Ts...>>(t)
      );
}

using namespace std;

int main()
{
   print(1,'2',3.14);
   print(make_tuple(1,'2',3.14));
}
