#pragma once
#include "animal_factory.h"

class WildAnimalFactory : public AnimalFactory {
  public:
  Animal* create(std::string const&) override;
};