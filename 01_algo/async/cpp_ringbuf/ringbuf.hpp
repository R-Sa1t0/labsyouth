#pragma once

#include <condition_variable>
#include <deque>
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