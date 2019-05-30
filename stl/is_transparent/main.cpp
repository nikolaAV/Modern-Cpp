#include <set>
#include <string>
#include <string_view>

/**
   Heterogeneous Lookup in Ordered Containers, C++14 Feature
   https://www.bfilipek.com/2019/05/heterogeneous-lookup-cpp14.html#whats-coming-in-c20
*/

using namespace std;

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
   double price()       const noexcept { return price_; }
};

inline bool operator<(const product& left, const product& right) { 
    return left.name() < right.name(); 
}

inline bool operator<(const product& left, const char* right) { 
    return left.name() < right; 
}

inline bool operator<(const char* left, const product& right) { 
    return left < right.name(); 
}

int main()
{
   const set<product> s1 {
      { "Car", "This is a super car that costs a lot", 100'000.0 },
      { "Ball", "A cheap but nice-looking ball to play", 100.0 },
      { "Orange", "Something to eat and refresh", 50.0 }      
   }; 
   
   // s1.find("Car"); Compile Error
   s1.find(product{"Car","",0.}); // Ok

   const set<product,less<>> s2 {
      { "Car", "This is a super car that costs a lot", 100'000.0 },
      { "Ball", "A cheap but nice-looking ball to play", 100.0 },
      { "Orange", "Something to eat and refresh", 50.0 }      
   }; 

   s2.find("Car"); // Ok
   s2.find(product{"Car","",0.}); // Ok
}
     