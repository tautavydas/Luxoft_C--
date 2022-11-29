#include <iostream>

class Base {
  public:
  virtual void foo() {
    std::cout << "Base::foo()" << std::endl;
  }
  // char data[300];
};
class Intermediate  :  virtual public Base {};
class Intermediate2 :  virtual public Base {};
class Intermediate3 :  virtual public Base {};

class Derived : public Intermediate, public Intermediate2, public Intermediate3 {
};


int main(int argc, const char** argv) {
    Derived d;
    std::cout << sizeof(d) << std::endl;
    // d.x = 20;
    // d.::Intermediate2::x = 12;
    // std::cout << &(d.Intermediate::x) << std::endl;
    // std::cout << &(d.Intermediate2::x) << std::endl;
    // std::cout << &(d.Intermediate3::x) << std::endl;
    
    // std::cout << d.x<< std::endl;
    // d.foo();
    
    // d.::Intermediate2::x = 10;
} 
