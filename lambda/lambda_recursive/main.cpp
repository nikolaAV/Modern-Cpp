
#include <functional>

// https://stackoverflow.com/questions/2067988/how-to-make-a-recursive-lambda
// https://stackoverflow.com/questions/35608977/understanding-y-combinator-through-generic-lambdas

template <typename R, typename A>
// https://en.wikipedia.org/wiki/Fixed-point_combinator
std::function<R(A)> Y(std::function<R(std::function<R(A)>,A)> f)
{
    return [f = std::move(f)](auto&& v){ 
        return f(Y(f), std::forward<decltype(v)>(v)); 
    };
}

#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

int main()
{
    auto const input = {0,1,2,3,4,5,6};
    auto output = std::vector<int>{};
    output.reserve(input.size());

    std::transform(input.begin(), input.end(), std::back_inserter(output), 
         // self - is an actual factorial algorithm with signature int f(int)
         // Y combinator is a responsible to invoke 'self' recursively
         Y<int,int>([](auto&& self, int value) {
               return value==0? 1 : value * self(value-1);
         })
    );

    std::copy(output.begin(), output.end(), std::ostream_iterator<int>(std::cout, "\n"));
}
