# Variatic Templates. A few useful examples

## Element Enumeration
Let's suppose we want to get a string representation for the sequence of bits like that:
```cpp
    template <bool... bits>
    string print() { ??? }

	cout << print<1, 1, true, false, 0, 1, false>() << endl;
   // output: 1110010 
```
It can be done by means expansion of parameter pack 'bits' with several ways:
* recursive variadic function
* recursive variadic type
* function parameter list
* brace-enclosed initializers
* fold-expressions (since C++17)
 
### Further informations
* [cppreference.com::parameter_pack](http://en.cppreference.com/w/cpp/language/parameter_pack)
* [C++17, New Features](http://scrutator.me/post/2017/08/11/cpp17_lang_features_p1.aspx) by Evgeniy Shcherbina

### Related links
* [Generating cartesian product pairs of any input at compile time](../lambda/lambda_cartesian)
* [Callling multiple functions with the same input](../lambda/lambda_multicall)

## Inheritance Generation

TBD

## Universal Delegate

[readme](https://github.com/nikolaAV/Modern-Cpp/tree/master/variadic/universal%20delegate)
 
