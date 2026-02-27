#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <chrono>

using namespace std;

class print_implementation
{
    private:
        bool which_thread = false;          // false - foo || true - bar
        mutex mut;
        condition_variable next_thread;
    public:
        void foo()
        {
            unique_lock<mutex> ul(mut);
            next_thread.wait(ul, [this](){
                return !which_thread;
            });
            
            which_thread = !which_thread;
            ul.unlock();                    // Unlock early as cout don't need mutex
            cout << "foo";
            next_thread.notify_one();
        }

        void bar()
        {
            unique_lock<mutex> ul(mut);
            next_thread.wait(ul, [this](){
                return which_thread;
            });

            which_thread = !which_thread;
            ul.unlock();
            cout << "bar";
            next_thread.notify_one();
        }
};

int main()
{
    print_implementation implement;
    thread thread_foo([&implement](){
        for(int i = 0; i < 10; i++)
        {
            this_thread::sleep_for(chrono::milliseconds(100));
            implement.foo();
        }
    });

    thread thread_bar([&implement](){
        for(int i = 0; i < 10; i++)
        {
            this_thread::sleep_for(chrono::milliseconds(100));
            implement.bar();
        }
    });

    thread_bar.join();
    thread_foo.join();

    cout << "\n Done!" << endl;

    return 0;
}