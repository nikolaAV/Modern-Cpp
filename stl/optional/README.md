# [`std::optional`](https://en.cppreference.com/w/cpp/utility/optional) makes code simpler
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
where 'lookup' declared as
```cpp
template <typename ContainerT, typename KeyT>
std::variant<ContainerT::iterator_to_value> lookup(ContainerT& c, KeyT&& k);
```
Thus, if the search is a success (`std::variant<>::has_value()==true`) the returned value can be dereferenced to access the original value stored in the container.  

## Further informations
* [`std::optional`](https://en.cppreference.com/w/cpp/utility/optional)
* [A Wall of Your std::optional Examples](https://www.bfilipek.com/2018/06/optional-examples-wall.html)
## Related links
* [back to stl section](../)
## Compilers
* [GCC 7.3.0](https://wandbox.org/)
* [clang 6.0.1](https://wandbox.org/)
* Visual C++ 19.14 

