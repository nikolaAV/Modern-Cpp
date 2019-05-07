# C++ concept ([Concepts Lite](https://isocpp.org/blog/2013/02/concepts-lite-constraining-templates-with-predicates-andrew-sutton-bjarne-s))
A few alternative routes until C++ language supports [them](http://en.cppreference.com/w/cpp/language/constraints)

## Further informations
* using `std::enable_if`, for more details see [the article](https://habrahabr.ru/post/304728/)
* using wrappers that are implemented by means C++ structures with concept-specified interface as [function-members set](https://habrahabr.ru/post/151504/)
* [How to Make SFINAE Pretty](https://www.fluentcpp.com/2018/05/18/make-sfinae-pretty-2-hidden-beauty-sfinae/)
* [Detection Idiom - A Stopgap for Concepts](https://blog.tartanllama.xyz/detection-idiom/) by Simon Brand
* [Notes on C++ SFINAE](https://www.bfilipek.com/2016/02/notes-on-c-sfinae.html), [SFINAE Followup](https://www.bfilipek.com/2016/02/sfinae-followup.html) by Bartlomiej Filipek

## Related links
* Example of an approach based on `std::enable_if` to make set of overloaded [XOR cipher algorithm](https://github.com/nikolaAV/skeleton/blob/master/algorithm/simple_xor).
* `static_assert` is another mechanism to specify sort of types allowed as input parameter in [insert_sorted algorithm](https://github.com/nikolaAV/skeleton/tree/master/algorithm/insert_sorted) 
