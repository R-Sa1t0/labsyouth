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


  // 動的確保される配列 
  {
    size_t n = 3;
    std::unique_ptr<int[]> v(new int[n]);
    // v を使う。サイズが n であることは別途覚えておく必要がある。
  }   // std::unique_ptr<int[]> のデストラクタが delete[] を呼ぶ。

  // std::vectorを使うと安全で便利
  {
    size_t n = 3;
    std::vector<int> v(n);  // 内部的に連続するヒープメモリを確保
    // v を使う。v.size() でサイズも分かる。
  } // std::vector<int> のデストラクタがヒープメモリを開放
  /*
  デフォルトコンストラクタを持たない型でも、以下のように初期化できる
  {
    std::vector<A> v(n, A(arg0, arg1));
  }
  これだと、各要素が初期化後にコピーされる。そのため、以下のようにすると、ヒープメモリの確保は 1 回だけに抑えて、無駄なく要素毎に好きなコンストラクタを呼べる
  {
    std::vector<A> v;
    v.reserve(n);
    for (size_t i = 0; i < n; i++) {
        v.emplace_back(arg0, arg1);
    }
  }

  */


}