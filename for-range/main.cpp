#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

template <typename T>
struct my_container : private list<T>
{
   using base_t         = list<T>;
   using const_iterator = typename base_t::const_iterator;
   using iterator       = typename base_t::iterator;

   using base_t::base_t;

   const_iterator cbegin() const { return base_t::cbegin(); }
   const_iterator cend()   const { return base_t::cend(); }
   const_iterator begin()  const { return base_t::begin(); }
   const_iterator end()    const { return base_t::end(); }
   iterator       begin()        { return base_t::begin(); }
   iterator       end()          { return base_t::end(); }
};


template <typename CONTAINER_T>
void print(const CONTAINER_T& c)
{
   for (auto v : c)
      cout << v << ",";
   cout << endl;
}

int main()
{
   const int                  arr[] = {5, 3, 1, 3, 5, 2, 5};
   const vector<int>          vec(arr,arr+(sizeof(arr)/sizeof(arr[0]))); 
   const my_container<double> cont(vec.begin(),vec.end());

   print(arr);
   print(vec);
   print(cont);

   for_each(vec.begin(),vec.end(),[](int val){ cout << val << ","; });
   cout << endl;

   cout << "Press any key + <enter> to exit" << endl;
   cin.get(); 
}
