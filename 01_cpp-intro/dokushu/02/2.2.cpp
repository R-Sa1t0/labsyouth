#include <iostream>

class cl_test {
  // デフォルトでは非公開
  int i = 100;

  // publicは明示した場合のみ
public:
  int i2 = 200;
  // 明示的にprivate
private:
  int i3 = 300;
};

class cl_test2
{
public:
  void hello() {std::puts("Hello!");}
};

int main() 
{
  cl_test c;
  //  c.i = 0; ←非公開なのでできない
  //  c.i3 = 0; ←非公開なのでできない
  c.i2 = 500; // できる

  cl_test2 c2;
  c2.hello();
}