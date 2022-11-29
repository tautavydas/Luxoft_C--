#include <iostream>
#include <string>

class Wheel {
    public:
    Wheel(int id) : id_(id) {
        std::cout << "Wheel()" << std::endl;
    }
    Wheel(const Wheel& w) : id_(w.id_ + 10) {
        std::cout << "Wheel(const Wheel& w)" << std::endl;
    }
    ~Wheel() {
        std::cout << "~Wheel()" << std::endl;
    }
    int id_;
};

class Engine {
    public:
    Engine(int id) : id_(id) {
        std::cout << "Engine()" << std::endl;
    }
    Engine(const Engine& e) : id_(e.id_ + 10) {
        std::cout << "Engine(const Engine& e)" << std::endl;
    }
    ~Engine() {
        std::cout << "~Engine()" << std::endl;
    }
    int id_;
};

class Insurance {
    public:
    Insurance(int id) : id_(id) {
        std::cout << "Insurance()" << std::endl;
    }
    Insurance(const Insurance& i) : id_(i.id_ + 10) {
        std::cout << "Insurance(const Insurance& i)" << std::endl;
    }
    ~Insurance() {
        std::cout << "~Insurance()" << std::endl;
    }
    int id_;
};

class Car {
    public: 
        Car(const std::string& name, Wheel* w, Engine* e, Insurance* i):
        name_(name), wheel_(w), engine_(e), insurance_(i) {
            std::cout << "Car constructor" << std::endl;
        }
        // Car(const Car& c) : name_(c.name_ + "(Copy)"), 
        //                     wheel_(new Wheel(*c.wheel_)),
        //                     engine_(new Engine(*c.engine_)),
        //                     insurance_(new Insurance(*c.insurance_)) {
        //     std::cout << "Car copy constructor" << std::endl;
        // }
        ~Car() {
            std::cout << "Car destructor" << std::endl;
            delete wheel_;
            delete engine_;
            delete insurance_;
        }
        std::string name_;
    Wheel* wheel_;
    Engine* engine_;
    Insurance* insurance_;
};

class Car2 {
    public: 
        Car2(const std::string& name,
            Wheel& w,
            Engine& e,
            Insurance& i) : name_(name), wheel_(w), engine_(e), insurance_(i) {
            std::cout << "Car constructor" << std::endl;
        }
        ~Car2() {
            std::cout << "Car destructor" << std::endl;
                    }
    std::string name_;
    Wheel& wheel_;
    Engine& engine_;
    Insurance& insurance_;
};

std::ostream& operator<<(std::ostream& os, const Wheel& w) {
    os << "Wheel(" << w.id_ << ")";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Engine& e) {
    os << "Engine(" << e.id_ << ")";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Insurance& i) {
    os << "Insurance(" << i.id_ << ")";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Car& c) {
    os << "[" << &c <<"]Car(" << c.name_ << ") : " << *(c.wheel_) << ", " << *(c.engine_) << ", " << (*c.insurance_) << ")";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Car2& c) {
    os << "[" << &c <<"]Car(" << c.name_ << ") : " << c.wheel_ << ", " << c.engine_ << ", " << c.insurance_ << ")";
    return os;
}

int main() {
    Wheel* w = new Wheel(1);
    Engine* e = new Engine(2);
    Insurance* i = new Insurance(3);


    Car c1("c1", nullptr, e, i);
    // delete w;
    // delete e;
    // delete i;
    
    // Car2 car2 = Car2("car2", *w, *e, *i);


    std::cout << "car1:" << std::endl;
    std::cout << c1 << std::endl;

    // Car* c = new Car("MyCar", w, e, i);
    // std::cout << *c << std::endl;
    // Car* car2 = new Car(*c);
    // delete c;
    // std::cout << *car2 << std::endl;
    
    
    // Wheel w;
    // Engine e;
    // Insurance i;
    // Car2 c(*w, *e, *i);

    // delete e;
    // delete w;
    // delete i;
    // Car c(&w, &e, &i);
    // return 0;
    // Wheel* w = new Wheel();
    // Engine* e = new Engine();
    // Insurance* i = new Insurance();
    // Car* c = new Car(w, e, i);
    // std::cout << "wheel adress = " << w << std::endl;
    // std::cout << "engine adress = " << e << std::endl;
    // std::cout << "insurance adress = " << i << std::endl;
    // std::cout << "car adress = " << c << std::endl;
    // std::cout << "car wheel adress = " << c->wheel_ << std::endl;
    // std::cout << "car engine adress = " << c->engine_ << std::endl;
    // std::cout << "car insurance adress = " << c->insurance_ << std::endl;
    return 0;
}