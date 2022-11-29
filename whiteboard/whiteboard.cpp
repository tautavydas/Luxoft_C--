#include <iostream>
#include <string>
#include <fstream>


char stored_data[30] = {0};

void print_data(char* data = stored_data) {
  for (int i = 0; i < 30; i++) {
    std::cout << std::hex <<  "0x" << static_cast<int>(data[i]) << " ";
  }
  std::cout << std::endl;
}


class Stored {
  

  public:

  Stored():value_(42) {
  }

  Stored(int value):value_(value) {
  }

  void* operator new(size_t size) {
    static int pos = 0;
    if (pos == 16) {
      pos = 0;
    }
    std::cout << std::dec << "Allocating " << size << " bytes " << "pos = " << pos << std::endl;
    void* p = reinterpret_cast<void*>(&stored_data[pos]);
    pos += size;
    return p;
  }

  void* operator new[](size_t size) {
    std::cout << "Allocating array of " << size << " bytes" << std::endl;
    return reinterpret_cast<void*>(&stored_data[0]);
  }

  void operator delete[](void* p) {
    std::cout << "Deleting array" << p << std::endl;
  }

  void operator delete(void* p) {
    std::cout << "Deleting " << p << std::endl;
  }

  double value_;
};

std::ostream& operator<<(std::ostream& os, const Stored& s) {
  os << "Stored(" << s.value_ << ")";
  return os;
}

void stored_play() {
  Stored s1(1);
  Stored s2(2);
  print_data();
  Stored* s3 = new Stored(9887);
  print_data();
  std::cout << "*s3" << *s3 << std::endl;

  Stored* s4 = new Stored(333);
  print_data();
  std::cout << "*s3" << *s3 << std::endl;
  std::cout << "*s4" << *s4 << std::endl;

  Stored* s5 = new Stored(111);
  print_data();
  std::cout << "*s3 " << *s3 << std::endl;
  std::cout << "*s4 " << *s4 << std::endl;
  std::cout << "*s5 " << *s5 << std::endl;
  new Stored(321);
  s5->value_ = 999;

  std::cout << "*s3 " << *s3 << std::endl;
  std::cout << "*s4 " << *s4 << std::endl;
  std::cout << "*s5 " << *s5 << std::endl;
}


void stored_pay2() {
  Stored* s = new Stored[3];
  std::cout << "s[0] " << s[0] << std::endl;
  std::cout << "s[1] " << s[1] << std::endl;
  std::cout << "s[2] " << s[2] << std::endl;
  delete new Stored(152);
  std::cout << "s[0] " << s[0] << std::endl;
  std::cout << "s[1] " << s[1] << std::endl;
  std::cout << "s[2] " << s[2] << std::endl;
  delete[] s;
  print_data();
}

class Bar {
public:
    Bar(): a(0), b(0) {
        std::cout << "Bar()" << std::endl;
    }
    ~Bar() {
        std::cout << "~Bar()" << std::endl;
    }
  int a;
  int b;
};


std::ostream& operator<<(std::ostream& stream, Bar& bar) {
    stream << "Bar(" << bar.a << ", " << bar.b << ")";
    return stream;
}


class Foo {
  public:
    Foo() {
      std::cout << "Foo::Foo()" << std::endl;
    }
    ~Foo() {
      std::cout << "Foo::~Foo()" << std::endl;
    }

    void* operator new(size_t size) {
      std::cout << "Foo::operator new(size_t)" << std::endl;
      return ::operator new(size);
    }

    void* operator new(size_t, void* where ) {
      std::cout << "Foo::operator placment new " << where << std::endl;
      return where;
      // return ::operator new(size);
    }
    

    void operator delete(void* ptr) {
      std::cout << "Foo::operator delete(void*)" << std::endl;
      ::operator delete(ptr);
    }

  int a;
  int b;
};

std::ostream& operator<<(std::ostream& stream, Foo& foo) {
    stream << "Foo(" << foo.a << ", " << foo.b << ")";
    return stream;
}

void* operator new(size_t size) throw(std::bad_alloc) {
  std::cout << "operator new(size_t)" << std::endl;
  return malloc(size);
}

void operator delete(void* ptr) throw() {
  std::cout << "operator delete(void*)" << std::endl;
  free(ptr);
}


void foo_on_stack() {
  std::cout << "====================" << std::endl;
  std::cout << "foo_on_stack()" << std::endl;
  Foo foo;
  foo.a = 1;
  foo.b = 2;
  std::cout << foo << std::endl;
}

void foo_on_heap() {
  std::cout << "====================" << std::endl;
  std::cout << "foo_on_heap()" << std::endl;
  Foo* foo = new Foo();
  foo->a = 1;
  foo->b = 2;
  std::cout << *foo << std::endl;
  delete foo;
}


void bar_on_heap() {
  std::cout << "====================" << std::endl;
  std::cout << "bar_on_heap()" << std::endl;
  Bar* bar = new Bar();
  delete bar;
}
// 
int main() {
  // Stored* s = new Stored(333);
  char buf[30] = {0};
  std::cout << (void*)(buf) << std::endl;
  Foo* foo = new (buf) Foo();
  foo->a = 999;
  foo->b = 999;

  print_data(buf);

  return 0;
}