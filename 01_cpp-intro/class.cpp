#include <iostream>

/*
https://github.com/starpos/get-out-of-cpp-beginners/blob/master/class.md
POD classは
 - C構造体としてC関数に渡せる
 - memcpyでコピーできる
などの特徴を持つ
*/

//standard-layout かつ trivial なclass(POD)
struct {
  int a;
  char b;
  float c;
}
// standard-layout でも trivial でもない class (仮想関数を持つものなど)
struct MyClass {
    virtual void func() {
    }
    int a;
    float b;
};
