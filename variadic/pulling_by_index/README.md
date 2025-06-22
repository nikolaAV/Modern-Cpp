# Pulling a single item from a C++ parameter pack by its index.
Having a parameter pack as an input set of data we can get access to any element from it by its index.
And the easiest way to do that is to reuse STL


```cpp
#include <tuple>

template <std::size_t Index, typename... Ts>
decltype(auto) get(Ts&&... ts)
{
   return std::get<Index>(std::forward_as_tuple(std::forward<Ts>(ts)...));
}

// usage
std::cout << "The first item is: " << get<1>(42, 3.14, "Hello") << std::endl;
// output: 3.14
```

## Further informations
* [Pulling a single item from a C++ parameter pack by its index](https://devblogs.microsoft.com/oldnewthing/20240516-00/?p=109771)
* [C++20 idioms for parameter packs](https://www.scs.stanford.edu/~dm/blog/param-pack.html)
## Related links
* TBD
## Compilers
* [GCC 8.1.0](https://wandbox.org/)
* [clang 6.0.0](https://wandbox.org/)
* Visual C++ 19.14 
