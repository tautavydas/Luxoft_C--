#include "object.h"
#include <iostream>


// class ObjectImpl {
// public:
//     ObjectImpl(int x) : x_(x) {}
//     void foo() {
//         std::cout << "Impl::foo() x_ = " << x_ << std::endl;
//     }
//     int x_;
// };


class ObjectImpl {
public:
    ObjectImpl(int x) : x_(x) {}
    void foo() {
        std::cout << "Impl::foo() x_ = " << http_request.get(x) << std::endl;
    }
    double value_double_;
    int x_;
};

Object::Object(int x): 
  pimpl_(new ObjectImpl(x)) {
}

Object::~Object() {
    delete pimpl_;
}



void Object::foo() {
    pimpl_->foo();
}
