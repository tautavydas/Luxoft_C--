#include <iostream>

class A {
  public:
  void foo() {
    std::cout << "A::foo()" << std::endl;
  }
  void foo() const {
    std::cout << "A::foo() const" << std::endl;
  }
};



int main(int argc, const char** argv) {
    A a;
    const A a2;
    const A& reftoa = a;
    reftoa.foo();
    // a.foo(); 
    // a2.foo();
}