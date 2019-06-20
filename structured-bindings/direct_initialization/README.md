# Defining several variables of different types in a row.
Structured Bindings allow us to define several objects in one go, in a more natural way than in the previous versions of C++.
```cpp
// before C++17
auto ch  = '#';
auto i   = 0;
auto b   = true;
```
```cpp
// since C++17
auto [ch,i,b] = tuple{'#',0,true};
```
It even makes some instructions, which early were not compilable, correct now. 
```cpp
for(char ch = '#', int i = 0, bool b = true; i < 10; ++i) { // won't compile
...
} 
for (auto[ch,i,b] = tuple{'#',0,true } ; i < 10; ++i) { // Ok
...
}
```
## Further informations
* [3 Simple C++17 Features That Will Make Your Code Simpler](https://www.fluentcpp.com/2018/06/19/3-simple-c17-features-that-will-make-your-code-simpler/) by Jonathan Boccara
## Related links
TBD
## Supported Compilers
* clang 6.0.1
* gcc 7.3.0
