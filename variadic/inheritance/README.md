# template parameter pack expansion: inheritance
A short example how to use the inheritance as template parameter pack expansion
```cpp
template<typename... Types>
struct C: Types...
{
```

## Further informations
* [Variadic templates. Unpacking](http://scrutator.me/post/2013/01/18/template-innovations.aspx)

## Related links
* [nikolaAV\::modern-cpp\::overloaded-lambdas](https://github.com/nikolaAV/Modern-Cpp/tree/master/lambda/lambda_overloaded)

