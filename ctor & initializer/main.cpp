#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <initializer_list>

using namespace std;

namespace
{

void test_builtin_array()
{
    cout << "--- test_builtin_array ---" << endl;

    auto arr = new int[9] {9,8,7,6,5,4,3,2,1};
    cout << arr[0] << arr[1] << arr[2] <<arr[3] <<arr[4] << "..." <<arr[8];
    cout << endl;
    delete[] arr;
}

void test_vector_std()
{
    cout << "--- test_vector_str ---" << endl;

	const vector<int> vec = {1,2,3,4,5,6,7,8,9};
    for(const auto val: vec)
        cout << val << ",";
    cout << endl;
}

void test_map_std()
{
    cout << "--- test_map_str ---" << endl;

	const map<int,string> m = {{1,"first"},{2,"second"}};
    for(const auto val: m)
        cout << val.first << "," << val.second << ";";
    cout << endl;
}


namespace pod
{
    struct A
    {
        int x;
        int y;
    };

	template <typename OUT_T>
	inline
	OUT_T& operator<<(OUT_T& out, const A& a)
    {
        out << "{" << a.x << "," << a.y << "}";
        return out;
    }

    inline void print(const A& a)
    {
        cout << "pod::A -> " << a << endl;
    }

    inline A instance()
    {
        return {1,1};
    }
} // pod

namespace npod
{
    struct A
    {
        A() : x(-1), y(100) {}
        A(int _1, int _2) : x(_1), y(_2) {}
        int x;
        int y;
    };

	template <typename OUT_T>
	inline
	OUT_T& operator<<(OUT_T& out, const A& a)
    {
        out << "{" << a.x << "," << a.y << "}";
        return out;
    }

    inline void print(const A& a)
    {
        cout << "npod::A -> " << a << endl;
    }

    inline A instance()
    {
        return {2,2};
    }
}// npod

namespace user_t
{
    class A
    {
    public:
        A(const initializer_list<int>& list)
        {
            for(const auto val: list)
                cout << val << ",";
            cout << endl;
        }
        A(const initializer_list<double>& list)
        {
            for(const auto val: list)
                cout << val << ",";
            cout << endl;
        }
        A(const initializer_list<pair<int,string>>& list)
        {
            for(const auto val: list)
                cout << val.first << "," << val.second << ";";
            cout << endl;
        }
    };

}// user_t


void test_pod()
{
    cout << "--- test_pod ---" << endl;
    pod::A a1 {123,456};
    pod::A a2={987,654};
    cout << a1 << " " << a2 <<endl;
    pod::print({33,44});
    cout << pod::instance() <<endl;
}

void test_npod()
{
    cout << "--- test_npod ---" << endl;
//    npod::A a1();   // <- a1 is a function prototype (warning GCC, link error MsVC)
    npod::A a2{};
//    cout << a1 << " " << a2 <<endl;
	cout << a2 << endl;
	npod::print({ 55, 66 });
    cout << npod::instance() <<endl;
}


void test_user_initializer()
{
    cout << "--- test_user_initializer ---" << endl;
    user_t::A a1{1,1,1,1,1,2};
    user_t::A a2{1.,1.,1.,1.,1.,2.};
    user_t::A a3{{1,"a"},{2,"b"},{3,"c"},{4,"d"}};
}


}   // end of anonymous namespace


int main(int /*argc*/, char** /*argv[]*/)
{
   test_builtin_array();
   test_pod();
   test_npod();
   test_vector_std();
   test_map_std();
   test_user_initializer();

   cout << "Press any key + <enter> to exit" << endl;
   cin.get();
}
