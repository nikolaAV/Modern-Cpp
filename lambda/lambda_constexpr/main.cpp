#include <array>

template<typename Range, typename Func, typename T>
constexpr T accumulate(const Range& range, Func func, T init) {
   for(auto&& elem:range)
      init += func(elem);
   return init; 
}

int main()
{
   constexpr std::array arr{1,2,3,4,5};
   static_assert(1+4+9+16+25==accumulate(  arr
                                          ,[](auto x){ return x*x; }
                                          ,0)
   );
}
