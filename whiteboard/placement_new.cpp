#include <iostream>

#pragma pack(1)
class Foo {
  int val = 0;
  double dval = 0.0;
  short sval = 0;
  char cval = 0;
  public:

    Foo(){}

    Foo(int val): val(val) {
      std::cout << "Foo(" << val << ")" << std::endl;
    }
    ~Foo() {
      std::cout << "~Foo(" << val << ")" << std::endl;
    }

    void* operator new(size_t size , void* where) {
      std::cout << "Foo::operator new(size_t) where " << std::endl;
      return ::operator new(size);
    }

    // void* operator new[](size_t size, void* where) {
    //   std::cout << "Foo::operator new(size_t) on where " << where << std::endl;
    //   return malloc(size);
    //   // return ::operator new(size, where);
    // }
};

void* operator new(size_t size, void* where) throw(std::bad_alloc) {
  std::cout << "operator new(size_t) on where " << std::endl;
  return where;
  // return malloc(size);
  // return ::operator new(size, where);
}

void print_data(char* data, int count) {
  for (int i = 0; i < count; i++) {
    std::cout << std::hex <<  "0x" << static_cast<int>(data[i]) << " " << std::dec;
  }
  std::cout << std::endl;
}



int main() {
  // std::cout << sizeof(int) << std::endl;
  std::cout << sizeof(int) + sizeof(double) + sizeof(short) + sizeof(char)  << std::endl;
  std::cout << sizeof(Foo) << std::endl;
  char buf[sizeof(Foo)*10] = {0};
  print_data(buf, sizeof(Foo) * 10);
  Foo* foo = new (buf) Foo[10];
  print_data(buf, sizeof(Foo) * 10); 


  return 0;
}