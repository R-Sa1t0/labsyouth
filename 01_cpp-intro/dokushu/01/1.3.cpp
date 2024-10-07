#include <iostream>

int main(){
  int i = 42;
  std::printf("++i: %d\n", ++i);
  std::printf("i  : %d\n", i);
  std::printf("i++: %d\n", i++);
  std::printf("i  : %d\n", i);

  std::cout << sizeof(i) << std::endl;
  std::cout << sizeof(int) << std::endl;

  i += 1;
  i -= 1;

  i = (1 + 2) * (3 - 4);
}