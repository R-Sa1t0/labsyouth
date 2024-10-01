#include <chrono>
#include <condition_variable>
#include <deque>
#include <iostream>
#include <mutex>
#include <thread>

#include "ringbuf.hpp"

ringbuf rbuf(100000);

bool finished = false;
std::chrono::time_point<std::chrono::high_resolution_clock> start;

void producer() {
  puts("producer thread start.");
  start = std::chrono::high_resolution_clock::now();

  for (int i = 0; i < 1000000; i++)
    rbuf.push(i);

  finished = true;
  puts("producer thread end.");
}
void consumer() {
  puts("consumer thread start.");

  while (true) {
    rbuf.pop();

    if (finished == true) {
      auto end = std::chrono::high_resolution_clock::now();
      auto duration =
          std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
      std::cout << "time: " << duration.count() << std::endl;
      return;
    }
  }
}

int main() {
  std::thread th_p(producer);
  std::thread th_c(consumer);

  th_p.join();
  th_c.join();
}