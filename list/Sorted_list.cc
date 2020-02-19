#include "Sorted_list.h"

using namespace std;

#ifndef INT_MAX
#define INT_MAX 2147483647
#endif

Sorted_list::Sorted_list(std::initializer_list<int> il) : _sentinel{new Node{}}, _first{_sentinel} {
  _sentinel->previous = nullptr;
  _sentinel->next = nullptr;
  _sentinel->value = INT_MAX;

  for (int e : il) {
    add(e);
  }
}

Sorted_list::Node * Sorted_list::first() {
  return _first;
}

Sorted_list::Node * Sorted_list::last() {
  return _sentinel->previous;
}

void Sorted_list::add(int n) {
  for (auto it = first(); it != _sentinel; it = it->next) {
    if (it->value > n || it == _sentinel) {

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
  for (auto it = first(); it != _sentinel; it = it->next) {
    if ( it->value == n) {

      it->previous->next = it->next;
      it->next->previous = it->previous;

      delete it;

      return;
    }
  }
}

std::ostream& operator<<(ostream& os, Sorted_list sl) {
  for (auto it = sl.first(); it != sl.last()->previous; it = it->next) {
    os << it->value << ", ";
  }
  os << sl.last();

  return os;
}

string Sorted_list::to_string() {
  stringstream ss{};
  ss << (*this);
  
  return ss.str();
}