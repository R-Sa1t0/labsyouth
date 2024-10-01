#include <iostream>

int
main() 
{
  std::printf("%d\n", 5 < 4);
  std::printf("%d\n", 5 > 4);
  std::printf("%d\n", 5 <= 4);
  std::printf("%d\n", 5 >= 4);
  std::printf("%d\n", 5 == 4);
  std::printf("%d\n", 5 != 4);
  std::printf("%d\n", 1 != 2 && 1 != 2);
  std::printf("%d\n", 1 != 2 || 1 != 2);
  std::printf("%d\n", !(1 != 2));


  if (true)
  {
    std::puts("aa");
  }
  else if (true)
  {
    std::puts("bb");
  }
  else
  {
    std::puts("cc");
  }


  int i = 0;
  switch(i)
  {
    case 1:
      std::puts("aa");
      break;
    case 2:
      std::puts("bb");
      break;
    case 3:
      std::puts("cc");
      break;
    default:
      std::puts("dd");
      break;
  }


  int a = 2;
  switch(a)
  {
    case 1:
    case 2: // フォールスルー(fall trough)
    case 3:
      std::puts("Hello~!");
  }


  int b = -3;
//  int b = 3;
  // 条件演算子
  std::printf("%d\n", b < 0 ? -b : b);


  label:
//  {
    std::puts("aaa");
    int x = 100;
//  }
  if (false) goto label;
}