#include <atomic>
#include <stdio.h>
#include <thread>

const int C = 10000000;

std::atomic<int> g_x = 0;
std::atomic<int> g_y = C * 2;

void test(int x) {
  printf("  test x=%d\n", x);

  for (int i = 0; i < C; i++) {
    g_x++;
    g_y--;
  }

  printf("  test sum=%d\n", g_x.load() + g_y.load());
  printf("  test g_x=%d\n", g_x.load());
  printf("  test g_y=%d\n", g_y.load());
  puts("  test end");
}

int main() {
  int x = 5;

  std::thread th(test, x);
  puts("main");
  for (int i = 0; i < C; i++) {
    g_x++;
    g_y--;
    if (i == C / 2)
      printf("main1 sum=%d\n", g_x.load() + g_y.load());
  }

  printf("main1 g_x=%d\n", g_x.load());
  printf("main1 g_y=%d\n", g_y.load());

  th.join();
  puts("main join");
  printf("main2 g_x=%d\n", g_x.load());
  printf("main2 g_y=%d\n", g_y.load());
}