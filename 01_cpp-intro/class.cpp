#include <iostream>
#include <stdio.h>
#include <cstdio>
#include <memory>



// 以下の2つは同じ
class A1{
public:
  int A;
  char B;
  float C;  
};
struct A2{
  int A;
  char B;
  float C;  
};
// 以下の2つも同じ
class B1{
  int A;
  char B;
  float C;  
};
struct B2{
private:
  int A;
  char B;
  float C;  
};

/*
https://github.com/starpos/get-out-of-cpp-beginners/blob/master/class.md
POD classは
 - C構造体としてC関数に渡せる
 - memcpyでコピーできる
などの特徴を持つ
*/

//standard-layout かつ trivial なclass(POD)
struct C1 {
  int a;
  char b;
  float c;
};
// standard-layout でも trivial でもない class (仮想関数を持つものなど)
struct C2{
    virtual void func() {
    }
    int a;
    float b;
};


// コンストラクタとデストラクタ
// デストラクタは引数を持たない1つのみ、コンストラクタは仮引数の数や型が異なれば複数定義できる
struct A {
  // 複数のコンストラクタ
  A() { puts("A cstr"); }
  A(int a) {puts("A cstr int");}
  // コピーコンストラクタ
  A(const A&){}
  // ムーヴコンストラクタ
  A(const A&&){}

  // デストラクタは1つ
  ~A() { puts("A dstr"); }
};


struct D
{
  // クラスにはメンバ関数を定義できる
  void A(){puts("Hello!");}
};



// 関数オーバーロード
// 同じ名前の関数でも、仮引数の数や型が異なれば別の関数として扱える
void E();
void E(int A);
void E(char C);



int main() {
  // コンストラクタ, デストラクタ
  std::printf("Hello! 1\n");
  {
    A a;
    std::printf("Hello! 2\n");
  }
  std::printf("Hello! 3\n");
}