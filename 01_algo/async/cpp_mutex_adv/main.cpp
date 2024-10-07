#include <atomic>
#include <mutex>
#include <stdio.h>
#include <thread>
#include <unistd.h>

std::mutex g_mtx;

struct Lock {
  std::mutex *mtx_;
  // コンストラクタ
  Lock(std::mutex *mtx) {
    mtx_ = mtx;
    //    puts("lock");
    mtx_->lock();
  }
  // デストラクタ
  ~Lock() {
    //    puts("un lock");
    mtx_->unlock();
  }
};

const int C = 1000000;

int g_x = 0;
int g_y = C * 2;

void test(int x) {
  printf("  test x=%d\n", x);

  for (int i = 0; i < C; i++) {
    Lock lk(&g_mtx);
    //    g_mtx.lock();
    g_x++;
    g_y--;
    //    g_mtx.unlock();
  }

  printf("  test sum=%d\n", g_x + g_y);
  printf("  test g_x=%d\n", g_x);
  printf("  test g_y=%d\n", g_y);
  puts("  test end");
}

int main() {
  int x = 5;

  std::thread th(test, x);
  puts("main");
  for (int i = 0; i < C; i++) {
    int sum = 0;
    Lock lk(&g_mtx);
    //    g_mtx.lock();
    g_x++;
    g_y--;
    sum = g_x + g_y;
    //    g_mtx.unlock();

    if (i == C / 2)
      printf("main1 sum=%d\n", sum);
  }

  printf("main1 g_x=%d\n", g_x);
  printf("main1 g_y=%d\n", g_y);

  th.join();
  puts("main join");
  printf("main2 g_x=%d\n", g_x);
  printf("main2 g_y=%d\n", g_y);
}