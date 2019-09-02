# is_transparent or Heterogeneous Lookup in Ordered Containers
C++14 brought a interesting feature on _associative_ containers that was cruelly missing for certain use cases: 
the ability to search an _associative_ container with something that is semantically a key, even if it is not technically a key.  
The _associative_ containers  may store object that embed their own keys, 
that is to say that such objects have a subpart that is to be considered as a key, 
like an ID for example, while the object itself is to be considered as a value.
```cpp
class product {
   string name_;
   string description_;
   double price_;
public:
   product(string_view n, string_view d, double p)
   :   name_(n)
      ,description_(d)
      ,price_(p)
   {}
   string name()        const { return name_; }
   string description() const { return description_; }
   double price()       const { return price_; }
};
```
Every product has an property __name__, that provides a technical order by which the products are sorted in the set. 
To implement this [`std::set`](https://en.cppreference.com/w/cpp/container/set) requires that products have to be comparable by _less than_ operator.
```cpp
inline bool operator<(const product& left, const product& right) { 
    return left.name() < right.name(); 
}
```
This way, products are sorted by __name__ inside the set. 
This feature has been there since C++98.
```cpp
   const set<product> s {
      { "Car", "This is a super car that costs a lot", 100'000.0 },
      { "Ball", "A cheap but nice-looking ball to play", 100.0 },
      { "Orange", "Something to eat and refresh", 50.0 }      
   }; 
```
If you want to find a “Car” then you need to create temporary product and fill its name:
```cpp
    if(s.find(product{"Car","",0.})==s.end()) {...}
```
But we want to do such kind of search without temporary creation by specifying product name directly.  
```cpp
    if(s.find("Car")==s.end()) {...}
```
that is not compilable because of `std::set::find` expects a key as an object of product type. 
### Heterogeneous Lookup, C++14
While it was not possible in `C++11`, we can do that by using heterogeneous lookup, available since `C++14`. 
All you have to do is to use [`std::less<>`](https://en.cppreference.com/w/cpp/utility/functional/less) and implement correct comparison functions!
```cpp
   const set<product,less<>> s {...};

   inline bool operator<(const product& left, const char* right) { 
      return left.name() < right; 
   }

   inline bool operator<(const char* left, const product& right) { 
      return left < right.name(); 
   }
```
And now you can find a particular product by using `const char*`
```cpp
   if(s.find("Car")==s.end()) {...}
```
You are given to know how to use such this new search pattern, but how is it implemented?  
Essentially, C++14 fills the gap, by providing new overloads of the [`std::set::find`](https://en.cppreference.com/w/cpp/container/set/find) method. 
These overloads are template, so they could theoretically accept anything that can be compared with a product, including an property __name__.
```cpp
   iterator find(const Key& key); // C++11, type Key is a part of container type set<Key> 
   template <typename OtherKey> iterator find(const OtherKey& key); // since C++14
```
What’s the difference between those two lines:
```cpp
   set<product> s1;        // resolved to std::set<product,std::less<product>> 
   set<product,less<>> s2; // resolved to std::set<product,std::less<void>> 
```
where
```cpp
   template <>
   struct less<product> { 
      bool operator()(const product& left, const product& right) const {
         return left < right;
      }
   };
   template <>
   struct less<void> { 
      using is_transparent = int; // please refer to the section 'Further informations' below

      template <typename OtherKey1, typename OtherKey2>
      bool operator()(const OtherKey1& left, const OtherKey2& right) const {
         // 'left' and 'right' can be distinct types, but they need to be comparable. 
        return left < right;
      }
   };
```

## Further informations
* [Heterogeneous Lookup in Ordered Containers](https://www.bfilipek.com/2019/05/heterogeneous-lookup-cpp14.html#whats-coming-in-c20) by Bartlomiej Filipek
* [How to search a C++ set with another type than its key](https://www.fluentcpp.com/2017/06/09/search-set-another-type-key/) by Jonathan Boccara
* [`std::set::find`](https://en.cppreference.com/w/cpp/container/set/find)
* [Heterogeneous Lookup in Associative Containers](https://abseil.io/tips/144)
* [Self-identification for SFINAE](https://youtu.be/PFdWqa68LmA?t=1843) by Stephen Dewhurst on CppCon 2017
## Related links
* [back to stl section](../)
## Compilers
Requires compilers that are compliant to C++14 Standard
* [GCC 7.1.0](https://wandbox.org/)
* [clang 6.0.0](https://wandbox.org/)
* Visual C++ 19.14 
