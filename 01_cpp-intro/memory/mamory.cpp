#include <cstdio>
#include <memory>
#include <vector>
/*
struct A
{
    bool closed_;
    Resource resource_;
    A() : closed_(false), resourece(open_resource()) {}
    ~A() try {
        close();
    } catch (...)
    }
    void close() {
        if (closed_) return;
        close_resource(resource_);
        closed_ = true;
    }
};

void bad_code()
{
  A* p = new A;
  try {
    // 例外を投げるかも知れない操作
    delete p;
  } catch (std::exception&) {
    delete p;
    throw;
  }
}

struct SafeHeapA
{
  A* ptr;
  SafeHeapA() : ptr(new A) {}
  ~SafeHeapA() { delete ptr; }
};

void good_code()
{
  SafeHeapA s;
  // 例外を投げるかも知れない操作
}
*/

struct A
{
  int A;
};



int main(){
  // 危険、メモリリークしやすい (delete忘れが発生しやすい)
  {
    A *p = new A;
    // p を使った操作
    delete p;
  }
  // 安全
  {
    std::unique_ptr<A> p(new A);
    // p を使う
  }  // p の寿命。p が管理していた A 型のヒープオブジェクトは p のデストラクタによって自動的に delete される。


  // 動的確保される配列 (危ない)
  {
    size_t n = 3;
    std::unique_ptr<int[]> v(new int[n]);
    // v を使う。サイズが n であることは別途覚えておく必要がある。
  }   // std::unique_ptr<int[]> のデストラクタが delete[] を呼ぶ。

  //
  {
    size_t n = 3;
    std::vector<int> v(n);  // 内部的に連続するヒープメモリを確保
    // v を使う。v.size() でサイズも分かる。
  } // std::vector<int> のデストラクタがヒープメモリを開放

}