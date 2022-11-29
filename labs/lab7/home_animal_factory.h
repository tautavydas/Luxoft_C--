#pragma once
#include "animal_factory.h"

class HomeAnimalFactory : public AnimalFactory {
  public:
  Animal* create(std::string const&) override;
};