# [scope_guard](https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Scope_Guard). A variation of resource management object. 
The Standard Template Library provides RAII (resource acquisition is initialization) classes for managing pointer types, such as [`std::unique_ptr`](https://en.cppreference.com/w/cpp/memory/unique_ptr) and [`std::shared_ptr`](https://en.cppreference.com/w/cpp/memory/shared_ptr). 
Until the proposal [P0052R3](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2017/p0052r3.pdf) is accepted it would be nice to have something that can do a clean-up/completion routine which is bound by scope, ensuring execution at scope exit (as the object is destroyed).
```cpp
// Instead of this
{
    void* p = malloc(n);
    // ...
    free(p);
}
// much better writing the following
{
    void* p = malloc(n);
    auto _ = finally([p] { free(p); });
    // ...
}
// or even may be this one
    void* p = malloc(n);
    block_on_exit([&]{free(p);},[&]{
    // ...
    });
```

## Further informations
* [Beautiful code: final_act from GSL](https://www.bfilipek.com/2017/04/finalact.html) by Bartlomiej Filipek
* [P0052R3 - Generic Scope Guard](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2017/p0052r3.pdf) `std::scope_exit` proposal from Peter Sommerlad and Andrew L. Sandoval
* [Use a final_action object to express cleanup if no suitable resource handle is available](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#e19-use-a-final_action-object-to-express-cleanup-if-no-suitable-resource-handle-is-available) from C++ Core Guidelines

## Related links
* [A lamda extends language feature](../lambda_lock)
* [back to the section](../)

## Compilers
* [GCC 8.1.0](https://wandbox.org/)
* [clang 6.0.0](https://wandbox.org/)
* Microsoft (R) C/C++ Compiler 19.14 
