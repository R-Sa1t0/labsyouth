#include <iostream>
#include <string>

int main() 
{
  puts("Hello!");

  int arr[5];
  int arr1[5] = {1, 2, 3, 4, 5};
  int arr2[] = {1, 2, 3, 4, 5};
  int arr3[5] = {1, 2, 3}; // 残りは0で初期化される
  //  int arrx = arr0;  // ←できない


  // print_size
  std::printf("%lu\n", sizeof(arr));
  // print_len
  std::printf("%lu\n", sizeof(arr)/sizeof(arr[0]));

  char char_arr[] = {"hello, world!"};
  // 1文字ずつ
  char char_arr1[3];
  char_arr1[0] = 'h';
  char_arr1[1] = 'e';
  char_arr1[2] = '\n';


  std::string ex_str = "Hello!";
  ex_str = "Wooooooorld!"; // あとから本来より長い文字列を代入可能

}