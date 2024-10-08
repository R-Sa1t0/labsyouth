#include <chrono>
#include <condition_variable>
#include <deque>
#include <iostream>
#include <mutex>
#include <thread>

#include "ringbuf.hpp"

const int N = 100000;

ringbuf rbuf(100000);


void producer() {
  puts("producer thread start.");

  for (int i = 0; i < N; i++) {
    rbuf.push(i);
  }

  puts("producer thread end.");
}
void consumer() {
  puts("consumer thread start.");

  std::chrono::time_point<std::chrono::high_resolution_clock> start;
  start = std::chrono::high_resolution_clock::now();

  for (int i = 0; i < N; i++) {
    rbuf.pop();
  }

  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout << "time: " << duration.count() << std::endl;
}

int main() {
  std::thread th_p(producer);
  std::thread th_c(consumer);

  th_p.join();
  th_c.join();
}