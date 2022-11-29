#pragma once
#include "object.h"

template<typename T>
void Object<T>::foo() {
  std::cout << "Implementation from header" << std::endl;
}

