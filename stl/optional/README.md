# [`std::optional`](https://en.cppreference.com/w/cpp/utility/optional) makes code simpler
### Example 1. Cleaner interface for _associative_container_::find
If you often get annoyed typing repeatable code like this:
```cpp
const map<int, string>         digits{ {1,"one"},{2,"two"},... };
unordered_map <string, double> prices{ {"oranges",1.}, {"apples",2.},...};

if(auto it = digits.find(2); it != digits.end())
   cout << "digit is " << (*it).second << endl;
else
   cout << "unknown digit" << endl;

if (auto it = prices.find("apples"); it != prices.end())
   (*it).second = 3.14;
```
then you should be stimulated rewrite it so that it becomes more compact and clearer. 
One of possible implementation can be:
```cpp
if (auto digit = lookup(digits,2))
   cout << "digit is " << *digit << endl;
else
   cout << "unknown digit" << endl;

if (auto product = lookup(prices,"apples"))
   *product =3.14;
```
where ['lookup'](./main.cpp) declared as
```cpp
template <typename ContainerT, typename KeyT>
std::variant<ContainerT::iterator_to_value> lookup(ContainerT& c, KeyT&& k);
```
Thus, if the search is a success (`std::variant<>::has_value()==true`) the returned value can be dereferenced to access the original value stored in the container.  

### Example 2. Chain building for function calls
Imagine an application that shows the ZIP code for a given person based on an association with an address. For this problem, we have the following classes:
```cpp
struct zip_code {...};
struct address {...};
struct person {...};
struct query {...};
```
and functions:
```cpp
optional<query>    get_query(...);
optional<person>   get_person(const query&);
optional<address>  get_address(const person&);
optional<zip_code> get_zip_code(const address&);
```
Function person 'get_person(const query&) returns an instance of a 'person' that matches the specified search query, maybe by requesting some database. 
> These all functions have `std::optional` return type as a pretty [convenient way](https://code.egym.de/the-beauty-of-total-functions-e8c35fee2d87) to indicate either the function completed successful or failed.  

These functions might be composed together to solve our problem as a pipeline, i.e. series of functions sequentially applied:
```cpp
const auto q = get_query(<query_input>);
if (!q) return;
const auto p = get_person(*q);
if (!p) return;
const auto a = get_address(*p);
if (!a) return;
const auto z = get_zip_code(*a);
if (!z) return;

// use z, ...
```
Hmm..It seems to look relatively more verbose that it can be. 
The code would have been more impressive if we had managed to compose or chain the required operations in one sequence with an error handling left out of scope consideration. 
The code became slightly more complex to understand, and therefore to change. 
How do you like the following notation?  
__(query->person)and_then(person->address)and_then(address->zip_code)__  
Where __and_then__ is the usual function composition: evaluates the first function and then feeds its return value into the second function. 
Such pipeline of function applications can be reduced into a “single function”, which is the composition of the whole pipeline
```cpp
if (auto z = optional{<query_input>} >> get_query >> get_person >> get_address >> get_zip_code) {
// use z, ...
}  
```
where [overloaded `operator>>`](./main2.cpp) is a analog of __and_then__ i.e. it's a composition function.
> Fortunately, `std::optional<T>` is getting a [nice monadic interface](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2019/p0798r3.html) soon, and monads are, essentially, all about composition.  
> Another way of implementing __and_then__ is now under consideration in the C++ ISO Committee. See [`expected<T,E>` from boost](http://open-std.org/JTC1/SC22/WG21/docs/papers/2017/p0762r0.pdf)


## Further informations
* [`std::optional`](https://en.cppreference.com/w/cpp/utility/optional)
* [A Wall of Your std::optional Examples](https://www.bfilipek.com/2018/06/optional-examples-wall.html)
* [The beauty of Total Functions](https://code.egym.de/the-beauty-of-total-functions-e8c35fee2d87) by Rafael Varago 
## Related links
* [back to stl section](../)
## Compilers
* [GCC 7.3.0](https://wandbox.org/)
* [clang 7.0.0](https://wandbox.org/)
* Visual C++ 19.14 

