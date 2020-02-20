#include "Sorted_list.h"

using namespace std;

#ifndef INT_MAX
#define INT_MAX 2147483647
#endif

Sorted_list::Sorted_list(std::initializer_list<int> il) : _first{nullptr}, _sentinel{new Sorted_list::Node{}} {
  cerr<<"A";
  _sentinel->previous = _first;
  _sentinel->next = nullptr;
  _sentinel->value = INT_MAX;
  cerr<<"B";

  for (int e : il) {
    cerr<<"loop";
    add(e);
  }
}

Sorted_list::Node * Sorted_list::first() {
  return _first == _sentinel ? nullptr : _first;
}

Sorted_list::Node * Sorted_list::last() {
  return _sentinel->previous;
}

void connect(Sorted_list::Node* before, Sorted_list::Node* after) {
  if (before != nullptr) {
    before->next = after;
  }
  if (after != nullptr) {
    after->previous = before;
  }
}

void insert(Sorted_list::Node* before, Sorted_list::Node* n, Sorted_list::Node* after) {
  connect(before, n);
  connect(n, after);
}

void insert(Sorted_list::Node* before, int n, Sorted_list::Node* after) {
  Sorted_list::Node* nn = new Sorted_list::Node{};
  nn->value = n;
  insert(after, nn, before);
}

void insert_unordered(int n, Sorted_list::Node* a, Sorted_list::Node* b) {
  if (a->value < b->value) {
    insert(a, n, b);;
  } else {
    insert(b, n, a);
  }
}

void Sorted_list::add(int n) {
  if (first() == nullptr) {
    insert(nullptr, n, _sentinel);
    _first = _sentinel->previous;

    return;
  }
  for (auto it = first(); it != _sentinel; it = it->next) {
    if (it->value > n || it == _sentinel) {
      insert_unordered(n, it, it->previous);
      /*
      Node* n = new Node{};
      n->previous = it->previous;
      if (it != _first) {
        n->previous->next = n;
      } else {
        _first = n;
      }
      it->previous = n;
      n->next = it;
      */
      return;
    }
  }
}

void Sorted_list::remove(int n) {
  for (auto it = first(); it != _sentinel; it = it->next) {
    if ( it->value == n) {

      connect(it->previous, it->next);

      if (_first == it) {
        _first = it->next;
      }

      delete it;

      return;
    }
  }
}

std::ostream& operator<<(ostream& os, Sorted_list sl) {
  if (sl.last() != nullptr) {
    bool one_element = sl.last()->previous == nullptr;
    if (!one_element) {
      for (auto it = sl.first(); it != sl.last()->previous; it = it->next) {
        os << it->value << ", ";
      }
    }

    os << sl.last();
  }

  return os;
}

string Sorted_list::to_string() {
  stringstream ss{};
  ss << (*this);

  return ss.str();
}
