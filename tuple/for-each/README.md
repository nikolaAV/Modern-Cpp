# [for_each(TupleType& tuple, UnaryFunction f)](./tuple_for_each.h)
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
In file 'tuple_for_each.h' you can find three variants of possible implementation of element enumeration in the tuple:
* by means overloaded function template 
* by means partial specialization class template
* by means fold expression, [`std::apply`](https://en.cppreference.com/w/cpp/utility/apply) and lambda capture parameter pack (since C++17)
* by means fold expression and [`std::index_sequence`](https://en.cppreference.com/w/cpp/utility/integer_sequence)

## Further informations
The techniques which are used for enumeration of a tuple
* [overloaded function template](http://cpplove.blogspot.com/2012/07/printing-tuples.html)
* [primary & partial specialization class template](https://books.google.com.ua/books?id=9DEJKhasp7gC&pg=PA74&lpg=PA74&dq=I/O+for+Tuples+Chapter+5:+Utilities&source=bl&ots=_a2eJ5LwSI&sig=GmtHoo_u9a53dYxJHL3NwbW81ms&hl=en&sa=X&ved=0ahUKEwiGzOmlkY_SAhULr1QKHd1JDw4Q6AEIGjAA#v=onepage&q=I%2FO%20for%20Tuples%20Chapter%205%3A%20Utilities&f=false) 
* [Exploding tuples with fold expressions](https://blog.tartanllama.xyz/exploding-tuples-fold-expressions/)

## Related links
* TBD

## Compilers
* [GCC 8.1.0](https://wandbox.org/)
* [clang 6.0.0](https://wandbox.org/)
* Microsoft (R) C/C++ Compiler 19.14 
