# Callling multiple functions with the same input
Based on lambda expressions multiple receivers (set of elementary calls) can be packed as a single call.
```cpp
void foo(...data...)
{
   // Do something useful with ...data... 
}
void prologue(...data...)
{
   // foo(...data...) is being invoked ...
}
void epilogue(string_view, double)
{
   // commit changes!
}

int main()
{
   auto f = multicall::make(prologue,foo,epilogue);   
   f("Pi",3.1456);
```
were a possible implementation of "the single call" can be
```cpp
auto make = [](auto... funcs) {
   return [=](auto... params) {
      return std::initializer_list<int> {
         ((void)funcs(params...),0)...
      };
   };
};
```
No eny extra data structures are required, so the compiler has a single job to generate a binary without overhead.
Function `multicall::make` accepts an arbitrary number of functions as parameters and returns a lambda expression that also accepts an arbitrary number of parameters.
This way, we can define `auto call_all = multicall::make(f1,f2,f3);`, and then invocation of `call_all("Hello, World!");` leads to a sequence of calls: `f1("Hello, World!");`,`f2("Hello, World!");`,`f3("Hello, World!");`.  

## Further informations
* TBD

## Related links
* [Universal Delegate](https://github.com/nikolaAV/Modern-Cpp/blob/master/variadic/universal%20delegate/README.md#callfunctionargs)

## Compilers
* [GCC 8.1.0](https://wandbox.org/)
* [clang 6.0.0](https://wandbox.org/)
* Microsoft (R) C/C++ Compiler 19.14 
