#include <iostream>
#include <mutex>
#include <condition_variable>
#include <queue>

template <typename T>
class bounded_buffer
{
    private:
        queue<T> q;
        int max_mem;

        condition_variable not_full;
        condition_variable not_empty;

        mutex internal_mut;
    public:
        bounded_buffer(int _max_mem) : max_mem(_max_mem){}
        void produce(T val)
        {
            unique_lock<mutex> ul(internal_mut);
            not_full.wait(ul, []{return this.q.size() < this.max_mem;});

            q.push(val);
            not_empty.notify_one();
        }

        T consume(void)
        {
            unique_lock<mutex> ul(internal_mut);
            not_empty.wait(ul, []{return !this.q.empty()});

            T res = q.front();
            q.pop();

            not_full.notify_one();
        }
};