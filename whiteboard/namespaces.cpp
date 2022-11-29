#include <iostream>



namespace foo {


  void func() {
    std::cout << "func iplementaiton 1()" << std::endl;
  }
  void foo() {
    std::cout << "foo::foo()" << std::endl;
  }
}

namespace foo {
  void bar () {
    foo();
  }
}

namespace foo::nested::neste2 {
    void only_for_this_file() {
    std::cout << "only_for_this_file" << std::endl;
  }
  
        void bar() {
          std::cout << "foo::nested::nested2::bar()" << std::endl;
        }
        void zak() {
          std::cout << "foo::nested::nested2::zak()" << std::endl;
        }
}

namespace foo::nested {
        void bar() {
          std::cout << "foo::nested::bar()" << std::endl;
        }
        void zak() {
          std::cout << "foo::nested::zak()" << std::endl;
        }
}

namespace deep = foo::nested::neste2;

int main() {
  // using foo::nested::bar;
  using foo::nested::neste2::zak;


  deep::bar();
  deep::bar();
  zak();
  // foo::nested::neste2::foo();
  return 0;
}