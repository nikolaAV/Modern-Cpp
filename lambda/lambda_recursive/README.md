# Anonymous recursive lambda expression
Example:
```cpp
    std::transform(...
    or 
    std::for_each(...
    or ...
         // self - is an actual factorial algorithm with signature int f(int)
         // Y<result_type, argument_type> combinator is responsible to invoke 'self' recursively
         Y<int,int>([](auto&& self, int value) {
               return value==0? 1 : value * self(value-1);
         })
    );
```

## Further informations
* [How to make a recursive lambda](https://stackoverflow.com/questions/2067988/how-to-make-a-recursive-lambda)
* [Understanding Y Combinator through generic lambdas](https://stackoverflow.com/questions/35608977/understanding-y-combinator-through-generic-lambdas)
* [Fixed-point combinator](https://en.wikipedia.org/wiki/Fixed-point_combinator) on Wikipedia

## Related links
* TBD

## Compilers
* [GCC 8.1.0](https://wandbox.org/)
* [clang 6.0.0](https://wandbox.org/)
* Microsoft (R) C/C++ Compiler 19.14 
