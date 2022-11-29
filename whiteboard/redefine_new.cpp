#include <iostream>

char my_memory[35] = {0};
int memory_index = 0;

void print_my_memory() {
  for (int i = 0; i < 35; i++) {
    std::cout << std::hex <<  "0x" << static_cast<int>(my_memory[i]) << " " << std::dec ;
  }
  std::cout << std::endl;
}

void* operator new(size_t size) throw(std::bad_alloc) {
  void* p = reinterpret_cast<void*>(&my_memory[memory_index]);
  std::cout << "Allocating memory of " << size << " bytes on address " << p  << std::endl;
  memory_index += size;
  return p;
  // return malloc(size);
}

// void* operator new[](size_t size) throw(std::bad_alloc) {
//   std::cout << "Allocating array of " << size << " bytes" << std::endl;
//   void* p = reinterpret_cast<void*>(&my_memory[memory_index]);
//   memory_index += size;
//   return p;
// }

void operator delete(void* ptr) throw() {
  std::cout << "Freeing memory at " << ptr << std::endl;
  // free(ptr);
}

void  operator delete[](void* ptr) throw() {
  std::cout << "Freeing array at " << ptr << std::endl;
  // free(ptr);
}

class Foo {
  public: 
    Foo() {
      std::cout << "Foo()" << std::endl;
    }

    Foo(double value):value_(value) {
      std::cout << "Foo(" << value_ << ")" << std::endl;
    }
    ~Foo() {
      std::cout << "~Foo(" << value_ << ")" << std::endl;
    }

    void* operator new(size_t size) throw(std::bad_alloc) {
      static Foo f;
      return reinterpret_cast<void*>(&f);
      // std::cout << "Allocating memory for Foo of " << size << " bytes" << std::endl;
      // return ::operator new(size);
    }

    // void* operator new[](size_t size) throw(std::bad_alloc) {
    //   std::cout << "Allocating array of Foo size " << size << " bytes" << std::endl;
    //   return malloc(size);
    // }

    void operator delete(void* ptr) throw() {
      std::cout << "Freeing memory for Foo at " << ptr << std::endl;
      ::operator delete(ptr);
    }

    void operator delete[](void* ptr) throw() {
      std::cout << "Freeing array for Foo  at " << ptr << std::endl;
      ::operator delete[](ptr);
    }

    double value_ = 11;
    short short_value_ = 22;
    int int_value_ = 33;
};

int main() {
  Foo * foo_array = new Foo[12];

  // Foo* f = new Foo(1);
  // Foo* f2= new Foo(2);
  // Foo* f3 = new Foo(3);
  // Foo* f4 = new Foo(4);
  
  // std::cout << "f = " << f << std::endl;
  // std::cout << "f2 = " << f2 << std::endl;
  // std::cout << "f3 = " << f3 << std::endl;
  // std::cout << "f4 = " << f4 << std::endl;
  // std::cout << "f->value_ = " << f->value_ << std::endl;
  // print_my_memory();
  // Foo* foo_array = new Foo[3];
  // Foo f(123);
  // Foo* f = new Foo(123);
  // delete f;
  // print_my_memory();
  // delete f;
  // Foo f;
  return 0;
}