#include <cstdio>
#include <memory>

// is-a : あるクラスBはあるクラスAのサブクラス (AはBのスーパークラス)
// has-a : オブジェクトAとBがあり、AがBを内包しているとき、A has-a B

struct A
{
    virtual void f1() { :: puts("A::f1"); }
    void f2() { ::puts("A::f2"); }
    virtual ~A() {}
};

struct B : A
{
    void f1() { ::puts("B::f1"); }
    void f2() { ::puts("B::f2"); }
    void f3() { ::puts("B::f3"); }
    ~B() {}
};

// 多態 (polymorphism) 
int main()
{
    // new: メモリ確保
    A* p = new B;
    p->f1();  // B::f1 が表示される
    p->f2();  // A::f2 が表示される
    //p->f3();
    dynamic_cast<B*>(p)->f3();  // B::f3 が表示される
    ((B*)p)->f3();  // B::f3 が表示される
}