#include <iostream>

void func() {
  std::cout << "func implementation2()" << std::endl;
}

namespace {} // namespace blablabla {..}; using namespace blablabla;  

namespace foo::nested::neste2 {
  namespace {
    void only_for_this_file() {
      std::cout << "only_for_this_file" << std::endl;
    }
  };
}
