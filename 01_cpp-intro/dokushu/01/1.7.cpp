#include <iostream>

int main() {
  // カウントアップループ
  int i = 0;
  while (i < 5)
  {
    i++;
    std::printf("%d\n", i);
  }
  // カウントダウンループ
  int i2 = 5;
  while (i2 > 0)
  {
    i2--;
    std::printf("%d\n", i2);
  }
  // break;
  while (true)
  {
    std::puts("Hello!");
    break;
  }
  // continue;
  int i3 = 1;
  while (i3 < 5) 
  {
    i3++;
    std::puts("1Hello!");
    continue; // whileの式評価に戻る (無限ループ注意)
  }

  // whileではなくforの場合continueを使うときのi++忘れがなくなる
  for (int i =0; i < 5; i++)
    std::puts("H");

  // C++ではこれもできる
  int v[] = {-1, 2, 4, -100, 500};
  for (int v_tmp: v)
    std::printf("%d\n", v_tmp);

  // do whileの場合、whileの条件に関わらずdoは必ず1回実行される
  int i = 0;
  do {
    std::printf("%d\n", i);
  } while (n < 5);
}