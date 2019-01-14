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
* [overloaded-lambdas](../../lambda/lambda_overloaded)
* [Mixin-based Type](../mixins#mixin-based-type-how-to-introduce-easily-additional-information-without-changing-its-interface)
