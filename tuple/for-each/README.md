# for_each(TupleType& tuple, UnaryFunction f)
Applies the given function object f to every element in the tuple [first, last], in order.

Example: how we can print a tuple
```cpp
template<typename... Args>
ostream& operator<<(ostream& out, const std::tuple<Args...>& t)
{
    out << "tuple[" << sizeof...(Args) << "]: {";
        for_each(t, [&](auto v) { out << v << ", "; } );
    return out << "}";
}

int main()
{
 	std::cout << std::make_tuple(1, 2., "3") << std::endl;
}
// output
tuple[3]: {1, 2, 3, }

```

# Related links
The techniques which are used for enumeration of a tuple
* [overloaded function template](http://cpplove.blogspot.com/2012/07/printing-tuples.html)
* [primary & partial specialization class template] (https://books.google.com.ua/books?id=9DEJKhasp7gC&pg=PA74&lpg=PA74&dq=I/O+for+Tuples+Chapter+5:+Utilities&source=bl&ots=_a2eJ5LwSI&sig=GmtHoo_u9a53dYxJHL3NwbW81ms&hl=en&sa=X&ved=0ahUKEwiGzOmlkY_SAhULr1QKHd1JDw4Q6AEIGjAA#v=onepage&q=I%2FO%20for%20Tuples%20Chapter%205%3A%20Utilities&f=false) 

## Supported Compilers
* Microsoft (R) C/C++ Optimizing Compiler Version 19.00.xyz ([Visual Studio 2015](https://www.visualstudio.com/vs/visual-studio-express/))
It's because of C++14 compliance is required ([Generic (polymorphic) lambda expressions](http://en.cppreference.com/w/cpp/compiler_support))