#include "bounded_buffer.h"
#include <thread>
#include <chrono>

using namespace std;

int main()
{
    bounded_buffer<int> buffer(5);
    thread producer([&]() {
        for (int i = 1; i <= 10; ++i) {
            buffer.produce(i);
            cout << "[Producer] Pushed: " << i << endl;
            this_thread::sleep_for(chrono::milliseconds(100));
        }
    });

    thread consumer([&]() {
        for (int i = 1; i <= 10; ++i) {
            this_thread::sleep_for(chrono::milliseconds(150));
            int val = buffer.consume();
            cout << "[Consumer] Popped: " << val << endl;
        }
    });

    producer.join();
    consumer.join();

    cout << "Done!" << endl;
    return 0;
}