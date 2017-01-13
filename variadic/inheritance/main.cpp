#include <string>
#include <iostream>
#include <typeinfo>

using namespace std;

// concept Functor
//{
//  void operator()() const;
//};

struct A // implements Functor
{
    void operator()() const {cout << "struct A: " << v_ << endl; }
private:
    int v_{1968};
};

struct B // implements Functor
{
    void operator()() const {cout << "struct B: " << v_ << endl; }
private:
    const char* v_{"nikola"};
};

struct C // implements Functor
{
    void operator()() const {cout << "struct C: <void>" << endl; }
};

template <typename... Args>
// requires Functor<Args>...
struct For_Each;

template <typename Head, typename... Tail>
// requires Functor<Head>, Functor<Tail>...
struct For_Each<Head,Tail...>
{
    template <typename T>
    // requires Derivable<T> from Head and Tails...
    For_Each(const T& obj)
    {
        static_cast<const Head&>(obj)();
        For_Each<Tail...> next(obj);
    }
};

template <> struct For_Each<>
{
    template <typename T> For_Each(const T&) {}
};


#ifdef __GNUG__
    //in order to suppress: warning: base class 'struct <X>' has a non-virtual destructor [-Weffc++]
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Weffc++"
#endif // __GNUG__


template <typename... Types>
struct Composite : public Types...
{
    void operator()() const
    {
        typedef Composite<Types...> this_t;
        cout << "struct Composite: " << typeid(this_t).name() << endl;
        For_Each<Types...> enumerator(*this);
    }
};

#ifdef __GNUG__
    #pragma GCC diagnostic pop
#endif // __GNUG__


static void test()
{
    typedef Composite<A,B,C>            first_t;
    typedef Composite<C,B,A>            second_t;
    typedef Composite<first_t,second_t> super_t;

    super_t()();
}


int main(int /*argc*/, char** /*argv[]*/)
{
    test();

    cout << "Press any key + <enter> to exit" << endl;
    cin.get();
    return 0;
}
