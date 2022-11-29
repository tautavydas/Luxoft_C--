#pragma once
#include "animal.h"

class AnimalFactory {
  public:
  virtual Animal* create(std::string const&) = 0;
};
