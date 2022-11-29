#include <iostream>
#include <map>
#include <string>



template <typename T>
struct Foo {
  
  Foo(T val): val_(val) {}

  template<typename U>
  U foo1(U t) {
    return t + val_;
  }

  template<typename U>
  U foo2(U t);

  template <typename U>
  void bar(T t, U u, std::map<T, U> &map);

  T val_;
};

template <typename T>
template <typename U>
U Foo<T>::foo2(U t) {
  return t + val_;
}

template <typename T>
template <typename U>
void Foo<T>::bar(T t, U u, std::map<T, U> &map) {
  map[t] = u;
}


int main_method_template() {
  Foo<std::string> foo ("hello");
  std::map<std::string, int> res;
  foo.bar("world", 1, res);
  for (auto &p : res) {
    std::cout << p.first << " " << p.second << std::endl;
  }
  // std::cout << foo.foo<double>(1.32) << std::endl;
  return 0;
}


struct Bar {
  template<typename T>
  // virtual void do_something(T t) = 0; Not allowed
};

struct Derived : public Bar {
  template<typename T>
  void do_something(T t) {
    std::cout << "do something" << std::endl;
  }
};

void func(Bar* bar) {
  bar->do_something<int>(1); // Not allowed because Derived::do_something<int> won't be generated
}

int main() {
  Bar* b = new Derived();  
}