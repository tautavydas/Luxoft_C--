#include <iostream>


class Foo {
  public:
    Foo(int identifier):identifier_(identifier) {
      std::cout << "construct foo with " << identifier << std::endl;
    }

    ~Foo() {
      std::cout << "destruct foo with " << identifier_ << std::endl;
    }

    int identifier_ = 0;
};

std::ostream& operator<<(std::ostream& ss, Foo& f) {
    ss << "operator << Foo(" << f.identifier_ << ")";
    return ss;
}



void func() {
  static Foo* f = new Foo(42);
  std::cout << *f << std::endl;
  f->identifier_++;
  delete f;
  f = nullptr;
}

int main() {
  std::cout <<"Start" << std::endl;
  func();
  func();
  func();
  func();
  
  std::cout <<"End" << std::endl;
  return 0;
}