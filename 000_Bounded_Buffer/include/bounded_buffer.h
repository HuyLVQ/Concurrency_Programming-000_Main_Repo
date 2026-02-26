#ifndef BOUNDED_BUFFER_H
#define BOUNDED_BUFFER_H

#include <iostream>
#include <mutex>
#include <condition_variable>
#include <queue>

using namespace std;

template<typename T>
class bounded_buffer
{
    private:
        queue<T> q;
        int max_mem;

        condition_variable not_full;
        condition_variable not_empty;

        mutex internal_mut;
    public:
        bounded_buffer(int _max_mem);
        void produce(T val);
        T consume(void);
};

#endif
