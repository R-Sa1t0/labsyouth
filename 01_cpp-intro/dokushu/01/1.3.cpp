#include <iostream>

int main(){
  int i = 42;
  std::printf("++i: %d\n", ++i);
  std::printf("i  : %d\n", i);
  std::printf("i++: %d\n", i++);
  std::printf("i  : %d\n", i);

  sizeof(i);
  sizeof(int);

  i += 1;

  i = (1 + 2) * (3 - 4);
}