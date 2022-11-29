#include "home_animal_factory.h"

Animal* HomeAnimalFactory::create(const std::string& sort) {
  if (sort == "dog") {
    return new Dog;
  } else if (sort == "cat") {
    return new Cat;
  } else if (sort == "imaginary") {
    return new Imaginary;
  } else return nullptr;
}