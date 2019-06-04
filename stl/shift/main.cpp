#include <vector>
#include <array>
#include <algorithm>
#include <iostream>

/**
   How to shift elements inside the container?
   \see https://github.com/nikolaAV/Modern-Cpp/tree/master/stl/shift
*/

using namespace std;

void c03()
{
   vector v{ 1,2,3,4,5,6,7,8,9,10 };
   copy(v.rbegin() + 5, v.rbegin() + 10, v.rbegin() + 2);
   for(vector<int>::const_iterator i = v.begin(); i!=v.end(); ++i) 
      cout << *i << " ";
}

void c11()
{
   vector v{ 1,2,3,4,5,6,7,8,9,10 };
   copy_backward(begin(v), begin(v) + 5, begin(v) + 8);
   for (auto i : v) cout << i << " ";

   array a{ 1,2,3,4,5,6,7,8,9,10 };
   copy_backward(begin(a), begin(a) + 5, begin(a) + 8);
   for (auto i : a) cout << i << " ";
}

void c20()
{
   vector v{ 1,2,3,4,5,6,7,8,9,10 };
   shift_right(begin(v), begin(v) + 5, 3);
   for (auto i : v) cout << i << " ";

   array a{ 1,2,3,4,5,6,7,8,9,10 };
   shift_right(begin(a), begin(a) + 5, 3);
   for (auto i : a) cout << i << " ";
}

int main()
{
   c03();
   c11();
   c20();
}
     
