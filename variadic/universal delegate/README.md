# call(function,args...)
universal delegate is function call dispatcher which
* can call any function type (pure function, functor or lambda)
* has no restriction regarding passed arguments and their types
* can be customized to do some useful work before/after call execution, based on [RAII](http://www.stroustrup.com/bs_faq2.html#finally) 
* has no overhead

Example
```cpp
struct record { /*...*/ };
void    foo1();
void    foo2(const record&);
record  foo3();
template <typename T> T foo4(const T& t) // ...

// direct invocation
record r;
foo1();
foo2(r);
r = foo3();
r = foo4(r)

// indirect invocation by means universal delegate: call
// something routine work can be done arround direct invocation
// for instance, function invocation can be synchronized to meet the thread safety or can be registered in any external log system 
call(foo1);
call(foo2,r);
r = call(foo3);
r = call(foo4<record>, r);
```
where 'call' - possible implementation 
```cpp
template <typename Function, typename... Args>
inline 
typename std::result_of<Function(Args...)>::type
call(Function&& f, Args... args)
{
    // prologue, std::lock_guard<std::mutex> lock(g_i_mutex); as example 
    return f(std::forward<Args>(args)...);
    // epilogue
}
```

## Further informations
* TBD

## Related links
* [Modern-Cpp::forwarding-reference](https://github.com/nikolaAV/Modern-Cpp/tree/master/forwarding-reference) 

