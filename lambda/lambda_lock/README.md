# A lamda extends language feature
Lambdas are a game-changer and will frequently change the way you write code to make it more elegant and faster. 
Want a ['lock'](https://docs.microsoft.com/en-us/dotnet/csharp/language-reference/keywords/lock-statement) or similar language feature that’s not actually in the language? 
```cpp
// C#
lock( mut_x ) {
    ... use x ...
}
```
It may be done in familiar syntax using a lambda.
```cpp
lock( mut_x, [&]{
    ... use x ...
});
```
where 'lock' simulating language feature is implemented as:
```cpp
template<typename F> void lock( std::mutex& m, F f ) 
{ 
    std::lock_guard hold(m);
    f(); 
}
```
## Further informations
* [Elements of Modern C++ Style](https://herbsutter.com/elements-of-modern-c-style/) by Herb Sutter
* [Scope Guard](https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Scope_Guard)
* [std::lock_guard](https://en.cppreference.com/w/cpp/thread/lock_guard)

## Related links
* [what does lambda capture?](https://github.com/nikolaAV/Storehouse-Of-Knowledge/blob/master/questions/README.md#lambda-capture-of-globals)
* [block on exit](./../lambda_block_on_exit)

## Compilers
* [GCC 5.1.0](https://wandbox.org/)
* [clang 4.0.0](https://wandbox.org/)
* Microsoft (R) C/C++ Compiler 19.14 
