#include <iostream>

int main()
{
  int v = 42;
  int& vref = v;

  std::printf("v addr: %p\n", &v);
  std::printf("v val: %d\n", v);
  std::printf("vref addr: %p\n", &vref);
  std::printf("vref val: %d\n", vref);

  vref = 100;
  std::printf("v addr: %p\n", &v);
  std::printf("v val: %d\n", v);

  int i = 33;
  int& iref = i;
  int *ip = &i;
  int j = 44;

  std::printf("*ip: %d, %p\n", *ip, ip);
  std::printf("iref: %d, %p\n", iref, &iref);
  ip = &j;
  iref = j; // 参照は参照先を変えられない
  std::printf("*ip: %d, %p\n", *ip, ip);
  std::printf("ref: %d, %p\n", iref, &iref);

  int x = 5;
  int& xref = x;
  // xref = 100; ←できる
  const int& xref_const = x;
  // xref_const = 5; ←できない

  const int y= 200;
  const int& yref = y; // 普通の参照
  // int& yref2 = y; ←constは外せない
}