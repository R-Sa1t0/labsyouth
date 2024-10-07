#include <iostream>

struct product
{
  int id;
  int price;
  int stock;
};

void print_product(product p)
{
  std::printf("id: %d\n", p.id);
  std::printf("price: %d\n", p.price);
  std::printf("stock: %d\n", p.stock);
}

union u
{
  int a;
  int b;
  int c;
};

enum class enum_test : char
{
  v1,
  v2,
  v3 = 100,
  v4 // 101
};

int main() 
{
  product water;
  water.id = 1;
  water.price = 100;
  water.stock = 1000;

  product banana = {2, 300, 10};

  print_product(water);
  print_product(banana);

  u u = {42};
  std::printf("a: %p\n", &u.a);
  std::printf("b: %p\n", &u.b);
  std::printf("c: %p\n", &u.c);

  std::printf("a: %d\n", u.a);
  u.c = 100;
  std::printf("c: %d\n", u.c);
  std::printf("a: %d\n", u.a);


  enum_test e = enum_test::v3;
  std::printf("%d\n", static_cast<int>(e));
}