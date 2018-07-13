# C++17 currying with nested lambda exression
In mathematics and computer science, currying is the technique of translating the evaluation of a function that takes multiple arguments into evaluating a sequence of functions, each with a single argument.\
Example:
```cpp
void foo(int a1,int a2,int a3,int a4,int a5)
{
...
}
```
can be called as
```cpp
   f(1)(2)(3)(4)(5);
```
where `f` is defined like that
```cpp
   auto f = [](int a1){
               return [=](int a2){
                  return [=](int a3){
                     return [=](int a4){
                        return [=](int a5){
                           foo(a1,a2,a3,a4,a5);
                        };
                     };
                  };
               };
            };
```

## Further informations
* [Currying](https://en.wikipedia.org/wiki/Currying) on Wikipedia
* [zero-overhead C++17 currying](https://vittorioromeo.info/index/blog/cpp17_curry.html) by Vittorio Romeo

## Related links
* [Parallelized Direct Acyclic Grapf](https://github.com/nikolaAV/skeleton/tree/master/parallel_dag#header-library-that-enables-implicit-task-based-parallelism-in-a-sequential-c-code)

## Compilers
* [GCC 8.1.0](https://wandbox.org/)
* [clang 6.0.0](https://wandbox.org/)
* Microsoft (R) C/C++ Compiler 19.14 
