
#include <iostream>

void foo () {
  std::cout <<"foo()" << std::endl;
}

namespace test2 {
    void foo () {
    std::cout <<"test2::foo()" << std::endl;
  }
}

namespace test {
  void foo () {
    std::cout <<"test::foo()" << std::endl;
  }
  void bar() {
    ::test2::foo();
  }
}

int main() {
  test::bar();
  return 0;
}