#include "file.h"
#include <iostream>


// template<typename T>
// void Foo<T>::foo() {
//     std::cout << "foo from file1" << std::endl;
// }

void func1() {
    Foo<int> foo;
    foo.foo();
    std::cout << "func1 from file1" << std::endl;
}