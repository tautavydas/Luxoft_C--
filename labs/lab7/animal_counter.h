#pragma once
#include <string>
#include <map>

class AnimalCounter {
  public:
  void add_animal(const std::string& animal);
  void remove_animal(const std::string& animal);
  size_t count_of_animals(const std::string& animal) const;
  static AnimalCounter& instance();
  private:
  std::map<std::string, size_t> animals_;
};