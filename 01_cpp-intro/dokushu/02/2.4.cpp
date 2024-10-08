#include <iostream>

int func() {
  return 1;
}

int main() {
  auto i = func();
  auto i2 = 3.14;
//  auto j;

  int arr[] = {-100, 1, 2, 3, -333};
  for (auto i: arr)
  {
    std::cout << i << std::endl;
  }

  // auto arr[] = {200, 300, 400, 500}; ←できない
   auto arr4 = {200, 300, 400}; //←これは配列ではない
  // auto arr{200, 300, 400}; ←推論される型が条件によって異なるらしい
}