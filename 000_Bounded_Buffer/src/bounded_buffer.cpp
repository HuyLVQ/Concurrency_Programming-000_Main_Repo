#include "bounded_buffer.h"

template <typename T>
bounded_buffer<T>::bounded_buffer(int _max_mem) : max_mem(_max_mem){}

template <typename T>
void bounded_buffer<T>::produce(T val)
{
    unique_lock<mutex> ul(internal_mut);
    not_full.wait(ul, [this]{return q.size() < max_mem;});

    q.push(val);
    not_empty.notify_one();
}

template <typename T>
T bounded_buffer<T>::consume(void)
{
    unique_lock<mutex> ul(internal_mut);
    not_empty.wait(ul, [this]{return !q.empty();});

    T res = q.front();
    q.pop();

    not_full.notify_one();

    return res;
}

template class bounded_buffer<int>;