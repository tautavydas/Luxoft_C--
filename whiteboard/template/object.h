#pragma once
#include <iostream>
#include <vector>
#include <list>

template<typename T>
class Object {
public:
  // using ContainerType = std::vector<T>;
  typedef std::vector<T> ContainerType;
  // static int ContainerType;
  Object(T a) : vec(a) {}
  void foo();
  std::vector<T> get();
  private:
  std::vector<T> vec;
};


template<typename T>
Object<T> makeObject(T a) {
  // return value optimization
  return Object<T>(a);
}

template<typename T>
typename Object<T>::ContainerType Object<T>::get() {
  return vec;
}

template<>
class Object<double> {
public:
  using ContainerType = std::list<double>;
  
  Object(double a) {}
  void foo();

  std::list<double> get() {
    return vec;
  }
  private:
  std::list<double> vec;
};



void myfunc();
void myfunc2();

#include "object.impl.h"