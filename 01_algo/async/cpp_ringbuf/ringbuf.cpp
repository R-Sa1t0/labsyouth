#include <condition_variable>
#include <deque>
#include <iostream>
#include <mutex>
#include <thread>

#include "ringbuf.hpp"

ringbuf rbuf(5);

void producer() {
  puts("producer thread start.");

  for (int i = 0; i < 44; i++)
    rbuf.push(i);

  puts("producer thread end.");
}
void consumer() {
  puts("consumer thread start.");

  while (true) {
    int v = rbuf.pop();
    std::printf("%d\n", v);
  }
}

int main() {
  std::thread th_p(producer);
  std::thread th_c(consumer);

  th_p.join();
  th_c.join();
}