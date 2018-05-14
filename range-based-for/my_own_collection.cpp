#include <iostream>
#include <vector>
#include <list>


/**
   https://mbevin.wordpress.com/2012/11/14/range-based-for/   

   What should your collection class provide 
   to be compliant for using in 'range-based-for' statement?
*/

using namespace std;

namespace member_function
{
   /**
      Approach 1
      Two pairs of 'begin() + end()' member functions have to be defined.
      'Two pairs' mean: -const & non-const versions.
   */
   template <typename T>
   struct my_container : private list<T>
   {
      using base_t = list<T>;
      using base_t::base_t;

      auto begin()  const { return base_t::begin(); }
      auto end()    const { return base_t::end(); }
      auto begin()        { return base_t::begin(); }
      auto end()          { return base_t::end(); }
   };
}  // namespace: member_function

namespace global_function
{
   /**
      Approach 2
      Two pairs of 'begin() + end()' free-standing functions have to be defined 
         in namespace where your collection class is defined.
      'Two pairs' mean: -const & non-const versions for input parameters.
   */

   template <typename T>
   class my_container
   {
      list<T>  impl_;
   public:
      template< class InputIt >
      my_container(InputIt first, InputIt last) : impl_(first,last) {}
      list<T>&       iterable()       noexcept { return impl_; } 
      const list<T>& iterable() const noexcept { return impl_; } 
   };

   template <typename T>
   auto begin(my_container<T>& c)         { return begin(c.iterable()); }
   template <typename T>
   auto end(my_container<T>& c)           { return end(c.iterable()); }
   template <typename T>
   auto begin(const my_container<T>& c)   { return begin(c.iterable()); }
   template <typename T>
   auto end(const my_container<T>& c)     { return end(c.iterable()); }

}  // namespace: global_function

template <typename Range>
void print(const Range& r)
{
   for (auto v : r)
      cout << v << ",";
   cout << endl;
}

int main()
{
   auto init_list                               = {5, 3, 1, 3, 5, 2, 5};
   const vector<int>                            vec{init_list}; 
   const member_function::my_container<double>  cont1(init_list.begin(),init_list.end());
   const global_function::my_container<double>  cont2(init_list.begin(),init_list.end());

   print(init_list);
   print(vec);
   print(cont1);
   print(cont2);
}
