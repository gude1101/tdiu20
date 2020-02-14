#include "Sorted_list.h"

using namespace std;

#define INT_MAX 2147483647

Sorted_list::Sorted_list(std::initializer_list<int> il) : _first{new Node{}}, _last{_first} {
  _last->previous = nullptr;
  _last->next = nullptr;
  _last->value = INT_MAX;

  for (int e : il) {
    add(e);
  }
}

Node* Sorted_list::first() {
  return _first;
}

Node* Sorted_list::last() {
  return _sentinel.previous;
}

void Sorted_list::add(int n) {
  for (auto it = _first; it != _sentinel; it = it->next) {
    if (it->value > n || it == _last) {

      Node* n = new Node{};
      n->previous = it->previous;
      if (it != _first) {
        n->previous->next = n;
      } else {
        _first = n;
      }
      it->previous = n;
      n->next = it;

      return;
    }
  }
}

void Sorted_list::remove(int n) {
  for (auto it = _first; it != _sentinel; it = it->next) {
    if ( it->value == n) {

      it->previous->next = it->next;
      it->next->previous = it->previous;

      delete it;

      return;
    }
  }
}

Sorted_list::to_string() {
  stringstream ss{};
  ss << (*this);
  
  return ss.str();
}

std::ostream& operator<<(ostream& os, Sorted_list sl) {
  for (auto it = sl.first(); it != sl.last()->previous; it = it->next) {
    os << it->value << ", ";
  }
  os << sl.last();

  return os;
}
