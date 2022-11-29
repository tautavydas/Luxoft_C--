#include <sstream>
#include "animal.h"

GeneralAnimal::GeneralAnimal(std::string const name, std::string const type)
    : name_(name), type_(type), food_(0) {
  AnimalCounter::instance().add_animal(name_);
  count_ = AnimalCounter::instance().count_of_animals(name_);
}
std::string GeneralAnimal::say() const {
  std::stringstream ss;
  ss << "I am a " << type_ << " " << name_ << ", " << talk() << " and I feeded " << food_ << " kg";
  return ss.str();
}
std::string GeneralAnimal::type() const {return type_;}
void GeneralAnimal::eat(double const kg) {food_ += kg;}
int GeneralAnimal::count() const{return count_;}
GeneralAnimal::~GeneralAnimal() {AnimalCounter::instance().remove_animal(name_);}


WildAnimal::WildAnimal(std::string const name) : GeneralAnimal(name, "wild") {}


Horse::Horse() : Horse::WildAnimal("horse") {}
std::string Horse::talk() const {
  return "I have 4 legs";
}

Kenguru::Kenguru() : WildAnimal("kenguru") {}
std::string Kenguru::talk() const {
  return "I like to jump";
}


HomeAnimal::HomeAnimal(std::string const name) : GeneralAnimal(name, "home") {}


Dog::Dog() : HomeAnimal("dog") {}
std::string Dog::talk() const {
  return food_ < 30 ? "I am hungry" : "I not hungry any more";
}

Cat::Cat() : HomeAnimal("cat") {}
std::string Cat::talk() const {
  return "I am lazy";
}

Imaginary::Imaginary() : GeneralAnimal("imaginary", "imaginary") {}
std::string Imaginary::talk() const {
  return "I don't follow the rules";
}
std::string Imaginary::say() const {
  return talk();
}