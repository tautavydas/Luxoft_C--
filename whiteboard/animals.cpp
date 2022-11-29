#include <cstring>
#include <iostream>



class Animal {
  public:

  virtual void say() const {
    std::cout << "Animal::say()" << std::endl;
  }
  virtual void say() {
    std::cout << "not implemented" << std::endl;
  }

  virtual void eat() {
    std::cout << "not implemented" << std::endl;
  }

};

class Dog : public Animal {
  public:
  
  void say() override {
    std::cout << "bark" << std::endl;
  }

  void eat() final {
    std::cout << "dog eats" << std::endl;
  }
};

class Cat : public Animal {
  public:
  
  void say() final {
    std::cout << "Mew" << std::endl;
  }
};

class Tiger : public Cat {
  public:
  
  void say() const {
    std::cout << "Roar" << std::endl;
  }
};


class Human : public Animal {
  void say() override {
    std::cout << "Hello i am a human" << std::endl;
  }
};

void sing(Animal& animal) {
  animal.say();
}

void feed(Animal& animal) {
  animal.eat();
}

int main() {
  Dog dog;
  feed(dog);
  // Cat cat;
  // Human human;
  Animal* t = new Tiger();
  
  // sing(dog);
  // sing(cat);
  // sing(human);
  sing(*t);
  // a->foo();
  // std::cout << b.x << std::endl;
  return 0;
}