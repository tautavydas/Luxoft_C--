#include "wild_animal_factory.h"

Animal* WildAnimalFactory::create(std::string const& sort) {
  if (sort == "horse") {
    return new Horse;
  } else if (sort == "kenguru") {
    return new Kenguru;
  } else if (sort == "imaginary") {
    return new Imaginary;
  } else return nullptr;
}