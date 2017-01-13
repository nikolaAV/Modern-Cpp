#include <string>
#include <iostream>
#include <tuple>
#include <utility>

/**
   Idea comes from https://habrahabr.ru/post/248897/
                   https://habrahabr.ru/post/183830/
*/


namespace variant1
{

template <std::size_t...> struct sequence {};

template <std::size_t N, std::size_t... S>
struct make_range : make_range<N-1,N-1,S...>
{
};

template <std::size_t... S>
struct make_range<0,S...>
{
   using type = sequence<S...>;
};

template <typename F, typename... Types, std::size_t... Range>
inline void invoke_(F f,const std::tuple<Types...>& t, const sequence<Range...>)
{
   f(std::get<Range>(t)...);
}

template <typename F, typename... Types>
inline void for_all(const std::tuple<Types...>& t, F f)
{
   using range_t = typename make_range<sizeof...(Types)>::type;
   invoke_(f,t,range_t{});
}

} // variant1

/*
namespace variant2
{

struct invoker
{
   template <typename F, typename... Types>
   invoker(F f, Types... args)
   {
      f(args...);
   }
   invoker() = delete;
};

template <typename F, typename... Types>
inline void for_all(const std::tuple<Types...>& t, F f)
{
  const auto first = std::make_tuple(false);
   std::pair<bool,invoker> exemplar {std::piecewise_construct, first, t}; 
}

}
*/
/////

void my_function(const char* a1, long a2, double a3)
{
   std::cout << a1 << ", " << a2 << ", " << a3 << std::endl;
}


using namespace std;

int main(int /*argc*/, char** /*argv[]*/)
{
    const auto a = make_tuple("nikola", 1968, 26.04);
    variant1::for_all(a, my_function);

//    variant2::for_all(a, my_function);
    

    cout << "Press any key + <enter> to exit" << endl;
    cin.get();
    return 0;
}
