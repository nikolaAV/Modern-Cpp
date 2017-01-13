#include <string>
#include <iostream>
#include <array>
#include <cassert>

// Book [ISBN 978-5-93286-205-6] "The D Programming Language" (Andrei Alexandresku), page 120
// http://en.wikipedia.org/wiki/Hamming_weight
// http://bisqwit.iki.fi/source/misc/bitcounting/

using namespace std;

namespace runtime
{

size_t naive(size_t v)
{   // Naive bit counting: Iterates through all bits.
    size_t count{0};
    while(v)
    {
        count += (v&1);
        v >>=1;
    }
    return count;
}

size_t sparse(size_t v)
{   // Sparse-ones: Only iterates as many times as there are 1-bits in the integer.
    size_t count{0};
    while(v)
    {
        ++count;
        v &=(v-1);
    }
    return count;
}

namespace recursive
{

size_t naive(size_t v, size_t count=0)
{
    return v? naive(v>>1,count+(v&1)) : count;
}

size_t sparse(size_t v, size_t count=0)
{
    return v? sparse(v&(v-1),++count) : count;
}

}   // end of namespace 'recursive'

}   // end of namespace 'runtime'

namespace compilertime
{

constexpr size_t naive(size_t v, size_t count=0)
{
    return v? naive(v>>1,count+(v&1)) : count;
}

constexpr size_t sparse(size_t v, size_t count=0)
{
    return v? sparse(v&(v-1),++count) : count;
}

}   // end of namespace 'compilertime'


int main(int /*argc*/, char** /*argv[]*/)
{
    assert(2==runtime::naive(10));
    assert(0==runtime::naive(0));
    assert(8==runtime::naive(255));

    assert(2==runtime::recursive::naive(10));
    assert(0==runtime::recursive::naive(0));
    assert(8==runtime::recursive::naive(255));

    assert(2==runtime::sparse(10));
    assert(0==runtime::sparse(0));
    assert(8==runtime::sparse(255));

    assert(2==runtime::recursive::sparse(10));
    assert(0==runtime::recursive::sparse(0));
    assert(8==runtime::recursive::sparse(255));

    constexpr array<size_t,3> arr{compilertime::naive(10), compilertime::naive(0), compilertime::naive(255)};

    cout << arr[0] << arr[1] << arr[2] <<endl;
    cout << "Press any key + <enter> to exit" << endl;
    cin.get();
    return 0;
}

