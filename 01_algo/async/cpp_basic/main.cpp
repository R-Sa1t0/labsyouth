#include <stdio.h>
#include <thread>

// volatile int g_x = 0;
volatile int g_x = 0;

const int C = 10000000;

void test(int x) {
  puts("  test start");

  printf("  test x=%d\n", x);
  // AAA
  for (int i = 0; i < C; i++) {
    g_x++;
  }
  /// AAA
  printf("  test g_x=%d\n", g_x);

  puts("  test end");
}

int main(void) {
  int x = 5;
  std::thread th(test, x);

  puts("main");
  /// BBB
  for (int i = 0; i < C; i++) {
    g_x++;
  }
  /// BBB
  printf("main 1:g_x=%d\n", g_x);

  th.join();
  puts("main join");

  printf("main 2:g_x=%d\n", g_x);
}