// #include "file.h"
// #include "object.h"
#include <iostream>

// typedef to a type; 
// make_template function
// virtual function template 
// CRTP


// template methods
// variable template 

// template<typename T>
// Foo<T> create_foo(T val) {
//     Foo<T> foo(val);
//     return foo;
// }

template<typename T>
class Comparable {
public:
  bool operator>(const T& other) const {
    const T& var_this = *static_cast<const T*>(this);
    return var_other < var_this;
  }
  bool operator==(const T& other) const {
    const T& var_this = *static_cast<const T*>(this);
    return !(var_this < other) && !(other < var_this);
  }
};

class Foo : public Comparable<Foo> {
  //Mixing in C++
  public:
  Foo(int val) : val_(val) {}

  bool operator<(const Foo& other) const {
    return val_ < other.val_;
  }
  int val_;
};


int main(int argc, const char** argv) {
  Foo foo(1);
  Foo foo2(2);


  std::cout << std::boolalpha << (foo < foo2) << std::endl;
  std::cout << std::boolalpha << (foo > foo2) << std::endl;
  std::cout << std::boolalpha << (foo == foo2) << std::endl;
  
  

  // Bar * bar = new BarImpl<double>(7);
  // bar->foo();
  // Object<int> obj;
  // obj.foo();
    // func1();
    // func2();
    // Foo<double> foo(1.0);
    // auto vec = foo.bar<int>(5);
    // std::cout << vec[0] << std::endl;
    // std::cout << create_foo(5).bar<int>(123).capacity() << std::endl;
    return 0;
}