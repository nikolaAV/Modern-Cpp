# Fold expressions. Examples.

## Adding a range of values to a container.
Writing functions with any number of arguments is possible using variadic function templates. The function should have the container as the first parameter, followed by a variable number of arguments representing the values to be added at the back of the container. However, writing such a function template can be significantly simplified using fold expressions. Such an implementation is shown here:
```cpp
template <typename Container, typename... Values>
void push_back(Container& c, Values... vals)
{
   (c.push_back(std::forward<Values>(vals)),...);
}
```
And usage becomes in one line of the code:
```cpp
vector<int> v;
push_back(v,1,2,3,4,5,6,7,8,9,0);
```

## Container any, all, none
The requirement to be able to check the presence or absence of a variable number of arguments suggests that we should write variadic function templates. However, these functions require a helper function, a general-purpose one that checks whether an element is found in a container or not and returns a bool to indicate success or failure. Since all these functions, which we could call contains_all, contains_any, and contains_none, do is apply logical operators on the results returned by the helper function, we would use fold expressions to simplify the code. Short circuit evaluation is enabled after the expansion of the fold expression, which means we are evaluating only the elements that lead to a definitive result. So if we are looking for the presence of all 1, 2, and 3, and 2 is missing, the function will return after looking up value 2 in the container without checking value 3:
```cpp
template <typename Container, typename Value>
bool contains(const Container& c, const Value& v) {
   return std::end(c) != std::find(std::begin(c),std::end(c),v);
}

template <typename Container, typename... Values>
bool contains_any(const Container& c, Values&&... vals)
{
   return ( ... || contains(c,vals));
}

template <typename Container, typename... Values>
bool contains_all(const Container& c, Values&&... vals)
{
   return ( ... && contains(c,vals));
}

template <typename Container, typename... Values>
bool contains_none(const Container& c, Values&&... vals)
{
   return !contains_all(c,std::forward<Values>(vals)...);
}
```

## Further informations
* [Fold Expressions](https://www.bfilipek.com/2017/01/cpp17features.html#fold-expressions) by Bartlomiej Filipek
* [Fold expressions](https://en.cppreference.com/w/cpp/language/fold) on cppreference.com

## Related links
* Usage Example [zip iterator](https://github.com/nikolaAV/skeleton/tree/master/algorithm/zip_iterator), [expressive_condition](https://github.com/nikolaAV/skeleton/tree/master/algorithm/expressive_condition)
* [predicate composition](./../predicate_composition)
* [Jump to variadic section](../)

## Compilers
* [GCC 8.1.0](https://wandbox.org/)
* [clang 6.0.0](https://wandbox.org/)
* Microsoft (R) C/C++ Compiler 19.14 
