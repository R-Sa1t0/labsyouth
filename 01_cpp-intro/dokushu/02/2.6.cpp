#include <iostream>

int main() {
  std::printf("num: ");
  int i;
  std::cin >> i;
  printf("%d\n", i);
  std::puts("");

  std::printf("string: ");
  std::string str;
  std::cin >> str;
  std::cout << "[" << str << "]" << std::endl;
  std::puts("");

  std::printf("string2: ");
  std::string s;
  std::getline(std::cin, s);
//  std::getline(std::cin, s, '\n'); // ←これと同じ
  std::cout << "[" << s << "]"  << std::endl;
}