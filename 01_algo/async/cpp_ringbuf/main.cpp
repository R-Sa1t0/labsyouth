#include <condition_variable>
#include <deque>
#include <iostream>
#include <mutex>
#include <thread>

// ringbuf
class ringbuf {
private:
  std::deque<int> deq;
  std::mutex mtx;
  std::condition_variable cv;
  size_t ringbuf_cap;

public:
  // 初期化
  ringbuf(size_t cap) : ringbuf_cap(cap) {}

  void push(int v) {
    {
      std::unique_lock<std::mutex> lock(mtx);
      cv.wait(lock, [this] { return deq.size() < ringbuf_cap; });
      deq.push_back(v);
    }
    cv.notify_all();
  }
  int pop() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [this] { return !deq.empty(); });
    int v = deq.front();
    deq.pop_front();
    cv.notify_all();
    return v;
  }
};

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