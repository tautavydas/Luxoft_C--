#include <iostream>
#include <functional>

struct lambda_01 {
    std::string name;
    int& age;
    int count = 0;
    lambda_01(const std::string& _name, int& _age) : name(_name), age(_age) {}
    void operator()(int a) const {
       std::cout << name << " " << age << " lambda_01 call" <<  a << "counter = " << count << std::endl;
      //  count++;
      //  age = 100;
    };
};

struct Foo {
  Foo() {
    std::cout << "Foo()" << std::endl;
  }
  Foo(const Foo& f) {
    std::cout << "Foo(const Foo& f)" << std::endl;
  }
  void foo() {}
};


int main_basic_lambdas() {
  std::string name = "Alex";
  int age = 43;
  Foo f;
  auto mylambda = [name, &age, count = 0](int a) {
    std::cout << name << " " << age << " labda call" << a << "counter = " << count << std::endl;
    // count++;
    age = -5;
  };

  auto lambda2 = [=]() mutable {
    std::cout << "Lambda2 "  << name << " " << age  << std::endl;
    age = -100;
    name = "Alice";
    mylambda(1234);
  };

  auto lambda3 = [&]() { // const ref?
    std::cout << "Lambda3 "  << name << " " << age  << std::endl;
  };

  auto mylambda2 = lambda_01(name, age);

  mylambda(1);
  age++;
  mylambda(2);
  mylambda(2);
  mylambda(2);
  mylambda(2);
  
  mylambda2(1);
  age++;
  mylambda2(2);

  lambda2();
  std::cout << "main: " <<  name << " " << age << std::endl;
  lambda3();
  name = "Charlie";
  lambda3();
  return 0;
}

struct MyClass {
  auto foo() {
    return [this](int) -> int {
      return var_;
    };
  }
  int var_ = 42;
};

template<class T>
void debug_type();

int main() {
  MyClass cl;
  auto f = cl.foo();
  // debug_type<decltype(f)>();
  auto x = [](){};
  // decltype(x) x2 = [](){}; // Not possible because lambda is not real type
  // debug_type<decltype(x)>();
  cl.var_ = 100;
  std::cout << f(44) << std::endl;
  return 0;
}