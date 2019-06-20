# Structured bindings.
C++17 adds [structured bindings](https://isocpp.org/files/papers/P0144R1.pdf) for
* tuple-like objects ([`std::tuple`](https://en.cppreference.com/w/cpp/utility/tuple), [`std::pair`](https://en.cppreference.com/w/cpp/utility/pair))
* classes where all the non-static member are public or all public-only non-static members are in a single direct base class.

## Further informations
* [Structured binding declaration (since C++17)](https://en.cppreference.com/w/cpp/language/structured_binding)

## Related links
* [Adding C++17 structured bindings support to your classes](./user_type_support) describes what you need to do so that your class/struct is applicable in structured bindings declaration.
* [Direct initialization](./direct_initialization) allows to define multiple variables in init- `if`, `switch`, `for` statements
