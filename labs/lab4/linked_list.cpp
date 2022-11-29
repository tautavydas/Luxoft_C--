#include "linked_list.h"
#include <iostream>

LinkedList::LinkedList(): _first(nullptr) {}

LinkedList::LinkedList(std::initializer_list<int> list): _first(nullptr) {
  Node *node{nullptr};

  for(auto it{std::rbegin(list)}; it != std::rend(list); ++it) {
    node = new Node{*it, node};
  }

  _first = node;
}

LinkedList::LinkedList(LinkedList const& copy): _first(nullptr) {
  Node *prev{nullptr};

  for (Node const* item{copy._first}; item != nullptr; item = item->next) {
    Node *const node{new Node{item->value, nullptr}};

    if (item == copy._first) {
      _first = node;
    } else {
      prev->next = node;
    }

    prev = node;
  }
}
LinkedList::~LinkedList() {
  for (Node *tmp{nullptr}, *item{_first}; item != nullptr; tmp = item, item = item->next, delete tmp);
}

void LinkedList::removeAt(size_t const index) {
  size_t counter{0};

  for (Node *prev{nullptr}, *curr{_first}; curr != nullptr; prev = curr, curr = curr->next, ++counter) {
    if (counter == index) {
      if (curr == _first) {
        _first = curr->next;
      } else {
        prev->next = curr->next;
      }

      delete curr;
      break;
    }
  }
}

void LinkedList::insertAt(size_t const index, int const value) {
  size_t counter{0};

  for (Node *prev{nullptr}, *curr{_first}; curr != nullptr; prev = curr, curr = curr->next, ++counter) {
    if (counter == index) {
      Node *const node{new Node{value, curr}};

      if (curr == _first) {
        _first = node;
      } else {
        prev->next = node;
      }

      break;
    }
  }
}

size_t LinkedList::getLength() const {
  size_t counter{0};

  for (Node *item{_first}; item != nullptr; item = item->next, ++counter);

  return counter ? counter : -1;
}

bool operator==(LinkedList const& op1, LinkedList const& op2) {
  if (op1.getLength() == op2.getLength()) {
    for (LinkedList::Node const* item1{op1._first}, *item2{op2._first}; item1 != nullptr && item2 != nullptr; item1 = item1->next, item2 = item2->next) {
      if (item1->value != item2->value) {
        return false;
      }
    }
  } else {
    return false;
  }

  return true;
}

std::ostream& operator<<(std::ostream& os, LinkedList const& list) {
  for (LinkedList::Node const* item{list._first}; item != nullptr; item = item->next) {
    os << item->value << " ";
  }

  return os;
}
