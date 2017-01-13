#include <iostream>

using namespace std;

template <typename F>
struct destruction_policy
{
    explicit destruction_policy(F f) : f_(f) {}
            ~destruction_policy()      { f_();}

    destruction_policy()                                       = delete;
    destruction_policy(const destruction_policy&)              = delete;
    destruction_policy& operator=(const destruction_policy&)   = delete;
    destruction_policy(destruction_policy&&)                   = delete;
    destruction_policy& operator=( destruction_policy&&)       = delete;
private:
    F f_;
};

template <typename F1, typename F2>
void block_on_exit(F1 eraser, F2 body)
{
    destruction_policy<F1> local_val{eraser};
    body();
}

namespace member_function_1arg
{

struct A
{
    enum Status {ERROR,SUCCESS,UNDEFINED};

    void open()             { cout << "A::open" << endl; }
    void close(Status s)    { cout << "A::close, status: " << s << endl; }

    Status begin_batch()                { cout << "A::begin_batch" << endl;         return SUCCESS; }
    Status send_message(const char* m)  { cout << "A::send_message: " << m << endl; return SUCCESS; }
    Status end_batch()                  { cout << "A::end_batch" << endl;           return SUCCESS;}
};


static void test()
{
    cout << "test 'member_function_1arg': guard based on lambda for object" << endl;
    A a{};
    A::Status status{A::UNDEFINED};

    block_on_exit([&]{ a.close(status); }, [&]{
        a.open();
        status = a.begin_batch();
        status = a.send_message("message");
        status = a.send_message("message1");
        status = a.send_message("message2");
        status = a.end_batch();
    }); // end of block
}

} // end namespace 'member_function_1arg'


namespace free_function_1arg
{

typedef int HANDLE;

static HANDLE  create()                             { cout << "::create" << endl;   return 1968; }
static void    release(HANDLE h)                    { cout << "::release, handle:" << h << endl; }
static void    begin_batch(HANDLE)                  { cout << "::begin_batch" << endl;         }
static void    send_message(HANDLE, const char* m)  { cout << "::send_message: " << m << endl; }
static void    end_batch(HANDLE)                    { cout << "::end_batch" << endl;           }

static void test()
{
    cout << "test 'free_function_1arg': guard based on lambda for C style API functions" << endl;

    HANDLE h{111};
    block_on_exit([&]{ release(h); }, [&]{
        h = create();
        begin_batch(h);
        send_message(h,"message");
        send_message(h,"message1");
        send_message(h,"message2");
        end_batch(h);
    }); // end of block
}




} // namespace 'free_function_1arg'

int main(int /*argc*/, char** /*argv[]*/)
{
    member_function_1arg::test();
    free_function_1arg::test();


    cout << "Press any key + <enter> to exit" << endl;
    cin.get();
    return 0;
}
