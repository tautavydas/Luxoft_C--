#include "array.h"
#include <iostream>

Array::Array()
    : size_(0),
      array_(nullptr) {
}

Array::Array(int size)
    : size_(size),
      array_(new double[size_]) {
  allocated_memory() = size_ * sizeof(double);
}

Array::Array(std::initializer_list<double> list)
    : size_(list.size()),
      array_(new double[size_]) {
  allocated_memory() += size_ * sizeof(double);
  // for (auto* iter = list.begin(); iter != list.end(); ++iter) {
  //   array_[std::distance(list.begin(), iter)] = *iter;
  // }
  std::copy(list.begin(), list.end(), array_);
}

Array::Array(const Array& other)
    : size_(other.size_),
      array_(new double[size_]) {
  allocated_memory() += size_ * sizeof(double);
  // for (size_t index = 0; index < size_; ++index) {
  //   array_[index] = other.array_[index];
  // }
  std::copy(other.array_, &other.array_[other.size_], array_);
}

Array::Array(Array&& other)
    : size_(other.size_),
      array_(other.array_) {
  other.size_ = 0;
  other.array_ = nullptr;
}

Array& Array::operator=(const Array& other) {
  if (this != &other) {
    delete[] array_;
    allocated_memory() += abs(other.size_ - size_) * sizeof(double);
    size_ = other.size_;
    array_ = new double[size_];
    // for(size_t index = 0; index < size_; ++index) {
    //    array_[index] = other.array_[index];
    // }
    std::copy(other.array_, &other.array_[other.size_], array_);
  }
  return *this;
}

Array& Array::operator=(Array&& other) {
  if (this != &other) {
    delete[] array_;
    allocated_memory() = other.size_ * sizeof(double);
    size_ = other.size_;
    array_ = other.array_;
    other.size_ = 0;
    other.array_ = nullptr;
  }
  return *this;
}

Array::~Array() {
  allocated_memory() -= size_ * sizeof(double);
  delete[] array_;
}

double& Array::operator[](size_t index) {
  return array_[index];
}

size_t Array::size() const {
  return size_;
}

size_t& Array::allocated_memory() {
  size_t static memory = 0;
  return memory;
}

