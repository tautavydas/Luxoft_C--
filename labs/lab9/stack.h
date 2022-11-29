#pragma once
#include <iostream>

template<class T>
class Stack {
    public:
        Stack(int size);
        ~Stack();
        bool pop();
        bool push(T t);
        bool empty();
        T head();
        size_t get_size();

        void apply(std::function<int(int const&)> const& lambda) const {
            for (int i = 0; i < stack_fill_; ++i) {
                try {
                    arr_[i] = lambda(arr_[i]);
                } catch(...) {
                }
            }
        }

        void inspect(std::function<void(int&)> const& lambda) const {
            for (int i = 0; i < stack_fill_; ++i) {
                try {
                    lambda(arr_[i]);
                } catch(std::invalid_argument const& e) {
                } catch(std::runtime_error const& e) {
                    throw e;
                } catch(std::exception const& e) {
                    break;
                }
            }
        }


    private:
        int size_;
        T* arr_;
        int stack_fill_;
};

template<class T>
Stack<T>::Stack(int size) : size_(size), arr_(new T[size_]), stack_fill_(0) {}

template<class T>
Stack<T>::~Stack() {
    delete[] arr_;
}

template<class T>
bool Stack<T>::pop() {
    if (stack_fill_>0) {
        stack_fill_-=1;
        return true;
    }
    else {
        return false;
    }
}
template<class T>
bool Stack<T>::push(T t) {
    if (stack_fill_<size_) {
        arr_[stack_fill_] = t;
        stack_fill_+=1;
        return true;
    }
    else {
        return false;
    }
}

template<class T>
bool Stack<T>::empty() {
    return stack_fill_ == 0;
}

template<class T>
T Stack<T>::head() {
    return arr_[stack_fill_-1];
}

template<class T>
size_t Stack<T>::get_size() {
    return sizeof(T)*size_;
}


template<class T>
class Stack<T*> {
    public:
        Stack(int size);
        ~Stack();
        T* pop();
        bool push(T* t);
        bool empty();
        const T& head();
        size_t get_size();
    private:
        int size_;
        T** arr_;
        int stack_fill_;
};

template<class T>
Stack<T*>::Stack(int size) : size_(size), arr_(new T*[size_]), stack_fill_(0) {}

template<class T>
Stack<T*>::~Stack()  {
    for (int i=0; i < stack_fill_; i++) {
        delete arr_[i];
    }
    delete[] arr_;
}

template<class T>
T* Stack<T*>::pop()  {
    if (stack_fill_>0) {
        stack_fill_-=1;
        return arr_[stack_fill_];
    }
    else {
        return nullptr;
    }
}

template<class T>
bool Stack<T*>::push(T* t) {
    if (stack_fill_<size_) {
        arr_[stack_fill_] = t;
        stack_fill_+=1;
        return true;
    }
    else {
        return false;
    }
}

template<class T>
bool Stack<T*>::empty() {
    return stack_fill_ == 0;
}

template<class T>
const T&  Stack<T*>::head() {
    return *arr_[stack_fill_-1];
}

template<class T>
size_t Stack<T*>::get_size() {
    return sizeof(T)*size_;
}


template <class T>
size_t SizeOf(T t) {
    return t.get_size();
}