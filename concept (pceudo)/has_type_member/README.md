# Member-function detection at the compile-time(C++17)
Here is an example of 'has_function_sort' metafunction which allows you to widen your own 'sort' algorithm in generic style  
i.e. independently either given container has its own 'sort' or it does not.  

```cpp
template <typename ContainerT>
enable_if_t<has_function_sort_v<ContainerT>>
sort(ContainerT& c)
{
   cout << "Calling member function: sort" << endl;
   c.sort();
}

template <typename ContainerT>
enable_if_t<!has_function_sort_v<ContainerT>>
sort(ContainerT& c)
{
   cout << "Calling free-standing function: std::sort" << endl;
   std::sort(std::begin(c),std::end(c));
}

int main()
{
   vector<int> vector;
   list<int> list;
   sort(vector);
   sort(list);
```

## Further informations
* [Original Article](http://scrutator.me/post/2017/04/10/has_function_metaprogramming.aspx) by Evgeniy Shcherbina
* [std::void_t](http://en.cppreference.com/w/cpp/types/void_t) 
* [SFINAE](http://scrutator.me/post/2016/12/12/sfinae.aspx) 

## Related links
* [iterator_traits2](https://github.com/nikolaAV/skeleton/tree/master/iterator_traits2)

## Compilers
* Microsoft (R) C/C++ Optimizing Compiler Version 19.10.xyz with option [/std:c++latest](https://docs.microsoft.com/en-us/cpp/build/reference/std-specify-language-standard-version) ([Visual Studio 2017](https://www.visualstudio.com/vs/visual-studio-express/))
