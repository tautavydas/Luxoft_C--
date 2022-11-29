#include <cstring>
#include <iostream>

struct Foo {
  Foo(const std::string& name): name_(name) {
    std::cout << "Foo constructed " << name_ << std::endl;
  }
  ~Foo() {
    std::cout << "~Foo " << name_ << std::endl;
  }
  const std::string name_;
};


struct A {
  A(int x) : x_(x) { 
    std::cout << "A( " << x << ")" << std::endl; 
  }

  A(double x) : x_(x) { 
    std::cout << "A( double " << x << ")" << std::endl; 
  }

  ~A() { 
    std::cout << "~A()" << std::endl; 
  }
  int x_;
  Foo foo_{"A"};
};

struct B : A {
  B() : A(5.0) { std::cout << "B()" << std::endl; }  
  B(int x ) : A(x) { std::cout << "B( << " << x << ")" << std::endl; }  
  ~B() { std::cout << "~B()" << std::endl; }
  Foo foo_{"B"};
};

struct C : B {
  C() { std::cout << "C()" << std::endl; }
  ~C() { std::cout << "~C()" << std::endl; }
  Foo foo_{"C"};
};

int main() {
  C c;
  return 0;
}