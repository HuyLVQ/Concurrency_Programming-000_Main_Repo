#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

class implementation
{
    private:
        enum THREAD_STATE {
            IS_0, IS_ODD, IS_EVEN
        };

        shared_ptr<int> curr_val = make_shared<int> (1);

        THREAD_STATE thread_state = IS_0;
        mutex mut;
        condition_variable next_thread;

    public:
        void print_0()
        {
            unique_lock<mutex> ul(mut);
            next_thread.wait(ul, [this](){
                return thread_state == IS_0;
            });

            thread_state = IS_ODD;
            cout << "0";
            next_thread.notify_all();
        }

        void print_odd()
        {
            unique_lock<mutex> ul(mut);
            next_thread.wait(ul, [this](){
                return thread_state == IS_ODD;
            });
            
            thread_state = IS_EVEN;
            cout << *curr_val;
            *curr_val += 1;
            next_thread.notify_all();
        }

        void print_even()
        {
            unique_lock<mutex> ul(mut);
            next_thread.wait(ul, [this](){
                return thread_state == IS_EVEN;
            });
            
            thread_state = IS_0;
            cout << *curr_val;
            *curr_val += 1;
            next_thread.notify_all();
        }

        shared_ptr<int> get_curr_count()
        {
            return curr_val;
        }
};

int main()
{   
    int count;
    cout << "Type desired count" << endl;
    cin >> count;

    implementation imp;
    thread thread_0([&imp, count](){
        while(*imp.get_curr_count() <= count)
        {
            imp.print_0();
            this_thread::sleep_for(chrono::milliseconds(100));
        }
    });

    thread thread_odd([&imp, count](){
        while(*imp.get_curr_count() <= count)
        {
            imp.print_odd();
            this_thread::sleep_for(chrono::milliseconds(100));
        }
    });

    thread thread_even([&imp, count](){
        while(*imp.get_curr_count() <= count)
        {
            imp.print_even();
            this_thread::sleep_for(chrono::milliseconds(100));
        }
    });

    thread_0.join();
    thread_even.join();
    thread_odd.join();

    cout << "\n Done!";

    return 0;
}