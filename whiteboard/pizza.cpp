#include <cstring>
#include <iostream>

class IPizza {
  public:
  virtual void prepare () = 0;
  virtual int id() = 0;
};

class Pizza : public IPizza {
  public:

  virtual std::string topping() = 0;
  virtual std::string meat() = 0;

  public:
  Pizza()  {
    static int pizzas_id_ = 0;
    id_ = pizzas_id_++;
  }
  void prepare () override {
    std::cout << "Preparing " << topping() << " pizza with " << meat() << std::endl;
  }

  int id() override {
    return id_;
  }
  int id_;
};

std::string Pizza::topping()  {
    return "default topping";
}

std::string Pizza::meat()  {
    return "default meet";
}


class PepperoniPizza : public Pizza {
  private:
  std::string topping() override {
    return Pizza::topping();
    // return "totatos";
  };
  std::string meat() override {
    return "beef";
  };
};

class HawaiPizza : public Pizza {
  private:
  std::string topping() override {
    return "pineapple";
  };
  std::string meat() override {
    return "chicken";
  };
};

void preparefor(IPizza* pizza, int number_of_pizzas) {
  for (int i = 0; i < number_of_pizzas; i++) {
    pizza->prepare();
  }
}

class VegeterianPizza : public IPizza {
  public:
  void prepare () override {
    std::cout << "Preparing pure vegeterian pizza" << std::endl;
  }
  int id() override {
    return 0;
  }
};

int main() {
  // Pizza *pizza = new Pizza();
  PepperoniPizza peperoni;
  VegeterianPizza vegeterian;
  // HawaiPizza hawai;
  preparefor(&vegeterian, 2);
  // preparefor(&hawai, 2);

  // Pizza pizza3;
  // pizza3.prepare();
  // a->foo();
  // std::cout << b.x << std::endl;
  return 0;
}