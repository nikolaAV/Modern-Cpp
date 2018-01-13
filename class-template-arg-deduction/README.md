# C++17 Feature – Class Template Argument Deduction
With C++17, we get class template argument deduction. It is based on template argument deduction for function templates and allows us to get rid of the need for clumsy make_XXX functions.

```cpp
	// Now, instead of
	auto myPair = std::make_pair("Hello","World");
	// you can just do the above by simply writing
	std::pair myPair{"Hello","World"};
	// where T1,T2 (the types of the elements that the pair stores) are deduced as 'const char*'

	// If you provide your own user-defined deduction guide:
	pair(char const*,char const*) -> pair<std::string,std::string>;
	// then
	std::pair myPair{"Hello","World"};
	// will store two elements of 'std::string' type
```

Further Information
* [Class Template Argument Deduction](https://arne-mertz.de/2017/06/class-template-argument-deduction/) by Arne Mertz
* [Template argument deduction for class templates](http://www.bfilipek.com/2017/01/cpp17features.html#template-argument-deduction-for-class-templates) by Bartlomiej Filipek

## Related links


