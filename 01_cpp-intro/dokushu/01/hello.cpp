#include <iostream>

// 関数定義
void show_sum(int a, int b) {
  std::printf("%d\n", a+b);
}
int sum(int a, int b) {
  return a+b;
}

int main() {
  std::cout << "Hello, World!!" << std::endl;

  // 変数の定義
  int a;
  int ab, ac;
  int AB_C;
  
  // 変数の初期化
  int x1(0);
  int x2 = 1;
  int x3{2};
  int x4 = {3};

  // 修飾子
  const int y1 = 128;
  int const y2 = 256;

  // 関数の呼び出し
  show_sum(1, 2);
  int v1 = sum(1, 2);
  int v2{sum(1,2)};
  
  // 
}