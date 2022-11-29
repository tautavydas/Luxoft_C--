#include "animal_counter.h"

AnimalCounter& AnimalCounter::instance() {
  static AnimalCounter instance;
  return instance;
}

void AnimalCounter::add_animal(const std::string& animal) {
  ++animals_[animal];
}

void AnimalCounter::remove_animal(const std::string& animal) {
  --animals_[animal];
}
size_t AnimalCounter::count_of_animals(const std::string& animal) const {
  auto const it = animals_.find(animal);
  if (animals_.end() != it) {
    return it->second;
  }
  return 0;
}
