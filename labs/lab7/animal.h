#pragma once
#include "animal_counter.h"

class Animal {
  public:
  virtual std::string say() const = 0;
  virtual std::string type() const = 0;
  virtual void eat(double kg) = 0;
  virtual int count() const = 0;
  virtual ~Animal() = default;
};

class GeneralAnimal : public Animal {
  protected:
  std::string name_, type_;
  double food_;
  int count_;
  GeneralAnimal(std::string name, std::string type);
  ~GeneralAnimal() override;
  private:
  virtual std::string talk() const = 0;
  virtual std::string say() const;
  std::string type() const final;
  void eat(double kg) final;
  int count() const final;
};

class WildAnimal : public GeneralAnimal {
  protected:
  WildAnimal(std::string name);
};

class Horse : public WildAnimal {
  public:
  Horse();
  private:
  std::string talk() const final;
};

class Kenguru : public WildAnimal {
  public:
  Kenguru();
  private:
  std::string talk() const final;
};

class HomeAnimal : public GeneralAnimal {
  protected:
  HomeAnimal(std::string name);
};

class Dog : public HomeAnimal {
  public:
  Dog();
  private:
  std::string talk() const final;
};

class Cat : public HomeAnimal {
  public:
  Cat();
  private:
  std::string talk() const final;
};

class Imaginary : public GeneralAnimal {
  public:
  Imaginary();
  private:
  std::string talk() const final;
  std::string say() const final;
};