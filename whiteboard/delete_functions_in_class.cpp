#include <iostream>

class Foo {
public:
  
  Foo() = default;
  explicit Foo(int identifier):identifier_(identifier){
    std::cout << "construct foo with " << identifier << std::endl;
  }
  
  Foo(const Foo& other) = delete;
  // Foo(const Foo& other) : identifier_(other.identifier_) {
  //   std::cout << "copy constructor " << identifier_ << std::endl;
  // }
  
  Foo& operator=(const Foo& other) {
    std::cout << "copy assignment " << identifier_ << std::endl;
    identifier_ = other.identifier_;
    return *this;
  }


  int identifier_ = 0;
  
  private:

  friend void foo();
 
};

std::ostream& operator<<(std::ostream& ss, Foo& f) {
    ss << "Foo(" << f.identifier_ << ")";
    return ss;
}

void foo() {
  Foo f(1);
  // Foo f2(f);
  // f2 = f;
  // Foo f3(2);
  // Foo assigment_result = (f3 = f2);
}
int main(int argc, const char** argv) {
  foo();
  // std::cout << "assigment_result = " << std::boolalpha << assigment_result << std::endl;
  return 0;
}