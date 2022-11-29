#include <iostream>
 #include <unistd.h>
template <typename> struct DebugType;

class Foo {
public:
    explicit Foo() = default;
    explicit Foo(int i): identifier_(i) {
       std::cout << "construct foo with " << i << std::endl;
       sleep(1);
    }

    Foo(const std::initializer_list<int>& list) {
        std::cout << "init list" << std::endl;
    }
    explicit Foo(int a, int b ) {
        std::cout << "Foo("<< a << "," << b << ")" << std::endl;
    }
    int identifier_ = 0;
};

std::ostream& operator<<(std::ostream& ss, Foo& f) {
    ss << "Foo(" << f.identifier_ << ")";
    return ss;
}


void func(Foo arg) {
    std::cout << arg << std::endl;
}

int main(int argc, const char** argv) {

    for (int i = 0 ; i < 3 ; i++) {
      func(Foo(i));
    }

    return 0;
}