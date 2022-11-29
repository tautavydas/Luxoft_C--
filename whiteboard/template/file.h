#include <iostream>
#include <vector>
template<class T>
class Foo {
public:

  Foo(){};

  template<class U>
  Foo(U val) : vec(val) {}
  // typedef std::vector<T> vec_type;
  using vec_type = std::vector<T>;
  void foo();

  template<class U>
  Foo::vec_type bar(U u);

  std::vector<T> vec;
};

template<typename T>
void Foo<T>::foo() {
    std::cout << "foo from header" << std::endl;
}
template<typename T>
template<class U>
typename Foo<T>::vec_type Foo<T>::bar(U u) {
    std::cout << "bar " << u << std::endl;
    Foo<T>::vec_type vec;
    vec.push_back(u);
    return vec;
}

void func1();
void func2();
