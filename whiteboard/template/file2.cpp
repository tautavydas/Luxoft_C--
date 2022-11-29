#include "file.h"
#include <iostream>

// template<typename T>
// void Foo<T>::foo() {
//     std::cout << "foo from file2" << std::endl;
// }

void func2() {
    Foo<int> foo;
    foo.foo();
    std::cout << "func2 from file2" << std::endl;
}