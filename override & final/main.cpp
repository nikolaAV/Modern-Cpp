#include <string>
#include <iostream>

using namespace std;

struct B
{
    virtual void foo() const { cout << "B::foo" << endl; }
    virtual void bar()       { cout << "B::Bar" << endl; }
    virtual ~B() {}
};

struct D : B
{
    virtual void foo() const override { cout << "D::foo" << endl; }
    virtual void bar() override final { cout << "D::Bar" << endl; }
};

struct F final : D
{
    virtual void foo() const override { cout << "F::foo" << endl; }
    void bar()   { cout << "F::Bar" << endl; }
};

struct G : F {};

int main(int /*argc*/, char** /*argv[]*/)
{
    F f;
    B& b = f;
    b.bar();
    b.foo();

    cout << "Press any key + <enter> to exit" << endl;
    cin.get();

   return 0;
}
