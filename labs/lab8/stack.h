#pragma once
#include <iostream>

template<typename T>
class Stack {
  private:
  int index_;
  T * items_;
  public:
  size_t const capacity_;
  Stack(size_t const capacity)
    : index_(-1),
      capacity_(capacity),
      items_(new T[capacity]) {}

  ~Stack() {
    delete[]items_;
  }

  bool empty() const {
    return index_ == -1;
  }

  T const& head() const {
    return items_[index_];
  }

  bool push(T const value) {
    if (index_ + 1 < capacity_) {
      items_[++index_] = value;
      return true;
    }
    return false;
  }

  bool pop() {
    if (index_  != -1) {
      --index_;
      return true;
    }
    return false;
  }
};

template<typename T>
class Stack<T*>{
  private:
  int index_;
  T** items_;
  public:
  size_t const capacity_;
  Stack(size_t const capacity)
  : index_(-1),
    capacity_(capacity),
    items_(new T*[capacity]) {}
  ~Stack() {
    for (int i = 0; i <= index_; ++i) {
      delete items_[i];
    }
    delete items_;
  }

  bool empty() const {
    return index_ == -1;
  }

  T const& head() const {
    return *items_[index_];
  }

  bool push(T *const value) {
    if (index_ + 1 < capacity_) {
      items_[++index_] = value;
      return true;
    }
    return false;
  }

  T* pop() {
    if (index_ != -1) {
      return items_[index_--];
    }
    return nullptr;
  }
};

template<typename T>
size_t SizeOf(Stack<T> stack) {
  return stack.capacity_ * sizeof(T);
}

template<typename T>
size_t SizeOf(Stack<T*> stack) {
  return stack.capacity_ * sizeof(T);
}