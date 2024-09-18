#include <mutex>
#include <queue>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <thread>

std::mutex g_mtx;
std::queue<uint16_t> q;

void producer() {
  puts("producer thread start.");
  for (uint16_t i = 0; i < 900; i++) {
    std::lock_guard<std::mutex> lock(g_mtx);
    q.push(i);
  }
  puts("producer thread end.");
  return;
}

void consumer() {
  puts("consumer thread start.");
  while (true) {
    std::lock_guard<std::mutex> lock(g_mtx);
    if (!q.empty()) {
      uint16_t tmp = q.front();
      q.pop();
      printf("%d\n", tmp);
    }
  }
}

int main(void) {
  std::thread th_p(producer);
  std::thread th_c(consumer);

  th_p.join();
  th_c.join();
}