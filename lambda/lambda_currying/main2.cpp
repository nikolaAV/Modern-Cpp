#include <tuple>
#include <utility>
#include <type_traits>

template <typename Function, typename... Args>
class curried {
   Function func_;
   std::tuple<Args...> args_;

public: 
   curried(Function func, Args... args) : func_(std::move(func)), args_(std::make_tuple(std::move(args)...)) {}
   curried(Function func, std::tuple<Args...> args) : func_(std::move(func)), args_(std::move(args)) {}

   template<typename... RestArgs>
   decltype(auto) operator()(RestArgs&&... args) const
   {
      auto const input_part_args = std::make_tuple(std::forward<RestArgs>(args)...);
      auto const sum_args = std::tuple_cat(args_, input_part_args);

      if constexpr(std::is_invocable_v<Function, Args..., RestArgs...>)
         return std::apply(func_, sum_args);
      else 
         return curried<Function, Args..., RestArgs...>(func_, sum_args);
   }
};

template <typename Function, typename... Args>
curried<Function, Args...> make_curried(Function&& func, Args&&... args)
{
   return curried<Function, Args...>(std::forward<Function>(func), std::forward<Args>(args)...);
}


////// 

#include <iostream>

void foo(int a1, int a2, int a3, int a4, int a5)
{
   std::cout << "foo:"
      << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5
      << std::endl;
}

int main()
{
   foo(1,2,3,4,5);   
   {
      auto const c = make_curried(foo);
      c(11)(12)(13)(14)(15);
   }
   {
      auto const c = make_curried(foo,21,22);
      c(23)(24,25);
   }
}

