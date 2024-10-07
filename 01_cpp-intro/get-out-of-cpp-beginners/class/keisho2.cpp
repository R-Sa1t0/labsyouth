// 悪い例
struct A
{
  ~A() {}  // non-virtual destructor
};

struct B : A
{
   int *p;
   B() : p(new int(0)) {}
   ~B() { delete p; }
};

int main()
{
    A *a = new B();
    delete a;  // ~A() が呼ばれ、~B() は呼ばれないので、メモリリーク
}