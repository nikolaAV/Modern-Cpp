# Validating ISBNs.
Let's suppose you are to write a program that validates 10-digit values entered by the user, as a string, represent valid [ISBN-10](https://en.wikipedia.org/wiki/International_Standard_Book_Number) numbers. 
As experienced programmer you would have used an algorithm from the Standard Library rather than reinvented the wheels.  
This first attempt might be shown as follows:
```cpp
bool validate(std::string_view isbn)
{
   auto valid = false;
   if (isbn.size() == 10 &&
       std::count_if(std::begin(isbn), std::end(isbn), isdigit) == 10)
   {
      auto w = 10;
      auto sum = std::accumulate(
         std::begin(isbn), std::end(isbn), 0,
         [&w](int const total, char const c) {
            return total + w-- * (c - '0'); });

     valid = !(sum % 11);
   }
   return valid;
}
```
The function takes an ISBN as a string, and returns `true `if the length of the string is 10, all ten elements are digits, and the sum of all digits multiplied by their weight (or position) is a multiple of 11. 
It may be applicable in the code like this: 
```cpp
   const std::string codes[] = { 
       "9992158107"s    // Ok 
      ,"9971502100"s    // Ok
      ,"097522980X0"s   // Error, will be detected later if you do not forget to check yourself 
      ...

  for(const auto& s:codes)
    validate(s); 
```
The obtained implementation is good but it can be better if we have managed compiler time check to ensure that a ISBM string meets the specification. I.e. such validation can be done once at the place where it's defined. 
```cpp
   constexpr std::string_view codes[] = { 
       "9992158107"_isbn    // Ok 
      ,"9971502100"_isbn    // Ok
      ,"097522980X0"_isbn   // Compile Error
      ...
```
The implementation is easier that we may have thought.
```cpp
constexpr inline bool validate(const char* s, std::size_t size) noexcept {
   if(10!=size)
      return false;
   return (   10*(s[0]-'0')
            +  9*(s[1]-'0')
            // ...
          )
         %11==0; 
}

constexpr inline std::string_view operator"" _isbn(char const* s, std::size_t count) noexcept {
    assert(validate(s,count)); 
    return string_view(s,count);
}
```




## Further informations
* [International Standard Book Number](https://en.wikipedia.org/wiki/International_Standard_Book_Number)

## Related links
* [Computing with constexpr](../invocation_context)
* [Other examples of compile time computing](../)

## Compilers
* [GCC 8.1.0](https://wandbox.org/)
* [clang 6.0.1](https://wandbox.org/)
* Microsoft (R) C/C++ Compiler 19.16 
