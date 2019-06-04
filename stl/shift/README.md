# How to shift elements inside the container?
Let’s consider the case where we want to copy a subpart of a range over to a position further down the range. It could be that this new position is located before the end of the first subrange.  
For instance, consider this 1 to 10 range:  
![input](./input.png)

Say that we’d like to move the 1 to 5 subrange 3 positions down:  
![output](./output.png)

```cpp
vector v{ 1,2,3,4,5,6,7,8,9,10 };
```
### C++03
```cpp
copy(v.rbegin()+5, v.rbegin()+10, v.rbegin()+2);
for(vector<int>::const_iterator i = v.begin(); i!=v.end(); ++i) 
   cout << *i << " ";
```
### C++11
```cpp
copy_backward(begin(v), begin(v)+5, begin(v)+8);
for (auto i : v) cout << i << " ";
```
### C++20
```cpp
shift_right(begin(v), begin(v)+5, 3);
for (auto i : v) cout << i << " ";
```

## Further informations
* [Moving Ranges Around with STL Algorithms](https://www.fluentcpp.com/2018/04/13/moving-ranges-stl/) by Jonathan Boccara
* [`std::copy_backward` vs. `std::copy`+reverse_iterator](https://www.fluentcpp.com/2019/05/31/the-difference-between-stdcopy_backward-and-stdcopy-with-reverse-iterators/) by Jonathan Boccara
* [`std::shift_left`, `std::shift_right`](https://en.cppreference.com/w/cpp/algorithm/shift)
## Related links
* [back to stl section](../)
## Compilers
> `std::shift_left`, `std::shift_right` are not supported yet ...
* [GCC 7.1.0](https://wandbox.org/)
* [clang 6.0.0](https://wandbox.org/)
* Visual C++ 19.14 

