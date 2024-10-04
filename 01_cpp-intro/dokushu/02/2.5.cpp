#include <iostream>

using integer = int;
// typedefでも効果は同じ
typedef int bbb;

class test_class {
  void a(){
    inttt a = 1200;
  }
public:
  using inttt = int;
};

int main()
{
  int a = 24;
  integer b = 300;

  using num = integer;
  num c = 44;

  a = c; //できる
  
  test_class::inttt i = 100;
  a = i;
  using aaa =  test_class::inttt;
  aaa i2 = 200;
  i2 = i;

}