#include <iostream>


class Foo;

Foo* foo();

class Bar {
public:
    Bar() = default;
    explicit Bar(int identifier):identifier_(identifier) {
        std::cout << "construct bar with " << identifier << std::endl;
    }
    Bar(const Bar& other) {
        std::cout << "copy construct bar with " << other.identifier_ << std::endl;
        identifier_ = other.identifier_;
    }
    ~Bar() {
        std::cout << "destruct bar with " << identifier_ <<  std::endl;
    }
    int identifier_ = 0;
};

Bar global_bar(100);

class Foo {
public:
  Foo(int v):value_(v) {
    std::cout << "Foo(" << value_ << ")" << std::endl;
  }
  Foo(const Foo& other) {
    std::cout << "Foo(const Foo& other)" << std::endl;
    value_ = other.value_;
  }
  ~Foo() {

    std::cout << "~Foo(" << value_ << ")" << global_bar.identifier_ << std::endl;
  }
  int value_;
};

std::ostream& operator<<(std::ostream& ss, const Foo& f) {
    ss << "Foo(" << f.value_ << ")";
    return ss;
}


Foo global_foo(42);

Foo& foo() {
  return global_foo;
}

void func(Foo& f) {
  std::cout << "inside func" << std::endl;
}

// Foo bar() {
//   Foo f(42);
//   return f;
// }


int main(int argc, const char** argv) {
  std::cout << "after func " << std::endl;
  return 0;
}