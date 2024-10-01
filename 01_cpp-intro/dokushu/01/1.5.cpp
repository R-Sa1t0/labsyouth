#include <iostream>
#include <stdint.h>

// 型
struct types{
  // void a; ← error
  void type_ex() {std::puts("Hello!");} // voidは特殊
  char a;
  int b;
  signed int c;
  unsigned int d;
  short e;
  long f;
  long long g;
  float h;
  double i;
};

// prefix & suffix
struct ex {
  int a = 0;
  unsigned int b = 1u;
  long c = 2l;
  unsigned long d = 2ul;
  long long e = 2ll;
  unsigned long long f = 2ull;
  float g = 6.7f;
  double h = 8.9;
  char i = '0';
  char j[3] = "11";
  char k[100] = R"hello(12)hello"; // 生文字列リテラル

  unsigned int l = 0xab; //16進数
  unsigned int m = 01; // 8進数
  unsigned int n = 0b0101; // 2進数
  float o = 0x89.abp1f; // 16進数の浮動小数点リテラル
};

struct ptr{
  int i = 100;
  int* i_p = &i;
  int** i_pp = &i_p;

  int j = **i_pp;
};

struct ptr_const{
  int i = 100;
  int* const i_p = &i;
  int* const* i_pp = &i_p;

  int j = **i_pp;
};

struct null_ptr {
  int* i = 0; // ←実は0=nullptr わかりにくい
  int* j = nullptr;
};

struct cast {
  uint8_t a = 0;
  char b = static_cast<char>(a);
};

int main()
{
  char j[] = "aa11";

}