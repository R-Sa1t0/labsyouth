#include <cstdio>
#include <cstdint>
#include <cstddef>

struct A
{
    int64_t i;
    int64_t j;
};
struct B
{
    int i;
    int j;
    A *a;
};
struct C
{
    char c;
    uint64_t i;
};
struct D
{
    char c;
    char padding0[7];
    uint64_t i;
};
struct E
{
    char c;
    uint64_t i;
} __attribute__((packed));


int main() {
  ::puts("struct A");
  A a;
  printf("a:%p, i: %p, j: %p\n", &a, &a.i, &a.j);

  ::puts("struct B");
  B b;
  printf("b: %p, i: %p, j: %p, a: %p\n", &b, &b.i, &b.j, &b.a);

  ::puts("struct C");
  C c;
  printf("c:%p, c: %p, i: %p\n", &c, &c.c, &c.i);

  ::puts("struct D");
  D d;
  static_assert(offsetof(D, c) == 0);
  static_assert(offsetof(D, i) == 8);
  static_assert(sizeof(D) == 16);
  printf("d:%p, c: %p, i: %p\n", &d, &d.c, &d.i);

  ::puts("struct E");
  E e;
//  static_assert(offsetof(E, c) == 0);
//  static_assert(offsetof(E, i) == 1);
//  static_assert(sizesof(E) == 9);
  printf("e:%p, c: %p, i: %p\n", &d, &e.c, &e.i);

/*
以下の書き方は初期化されてない
  int i;
  int* i = new int;
静的領域(グローバル変数やstatic変数など)は初期化される
  static int i;

  struct A { int i; };
  A a;
上記の例では、a.iは初期化されていない
  struct A { int i; A() : i() {} }
  A a;
上記では、Aは初期化子を使って初期化済みとなる
*/

/*
  {
    A *b0, *b1;
    {
        std::unique_ptr<A> a0(new A);  // a0 が所有者
        b0 = a0.get();   // b0 は借用者
        std::unique_ptr<A> a1(std::move(a0));  // a0 から a1 に所有権が移動
        // a0 は nullptr を指すようになる
        b1 = a1.get();   // b1 は借用者
        // b0 も b1 も a1 と同じヒープオブジェクトを指している。

    }  // a0 は nullptr を指しているので何もしない。a1 のデストラクタでヒープオブジェクトを開放。
    // b0 および b1 は dangling pointer になる
  }
*/
}