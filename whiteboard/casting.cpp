#include <iostream>
// C-cast (Type)(variable) 
// (int) 1.3;
// f = (Foo*) p;
// int(1.5)

// static_cast<Type>(variable)
// class A {
//   public:

//   operator int() const { 
//     std::cout << "A::operator int()" << std::endl;
//     return 54; 
//   }
// };



// class Foo {
//   public:

//   int& operator[](bool cond) { 
//     return cond ? val1_ : val2_;
//   }

//   const int& operator[](bool cond) const { 
//     return const_cast<Foo&>(*this).operator[](cond);
//   }

//   private:
//   int val1_ = 10;
//   int val2_ = 10;
// };
// void read(const Foo& foo) {
//   std::cout << "f[false]" << foo[false] << std::endl;
//   std::cout << "f[true]" << foo[true] << std::endl;
// }


// Dynamic cast
// RTTI

// struct Base {
//   virtual ~Base() = default;
// };
// struct Derived :  Base {};
// struct Derived2 : public Base {};

// void foo(Base* b) {
//   Derived* d = dynamic_cast<Derived*>(b);
//   std::cout << "d: " << d << std::endl;
// }

// void foo(Base& b) {
//   Derived& d = dynamic_cast<Derived&>(b);
//   std::cout << "d: " << &d << std::endl;
// }



struct B {
  void foo() { std::cout << "B::foo()" << std::endl; }
  void foo() const { std::cout << "B::foo() const" << std::endl; }
};


void foo(B& b) {
  const_cast<const B&>(b).foo();
}

int main() {
  B b;
  foo(b);
  
  // Foo f;
  // f[false] = 100;
  // f[true] = 200;
  // read(f);
  // Base1* p = new D1();
  // static_cast<D2*>(p); // NO compile error

  // Derived d;
  // Derived *p = &d;
  // foo(p);
  // Base1 *b1 = static_cast<Base1 *> (p);  // upcasting 
  // Base2 *b2 = static_cast<Base2 *> (p);

  // std::cout << p << std::endl;
  // std::cout << b1 << std::endl;
  // std::cout << b2 << std::endl;
  // std::cout << d.y << std::endl;
    return 0;
}