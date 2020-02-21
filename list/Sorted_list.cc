#include "Sorted_list.h"

using namespace std;

#ifndef INT_MAX
#define INT_MAX 2147483647
#endif

// TODO: ta bort alla cerr<< när buggar är fixade

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

int* Sorted_list::Node::value_or_null(Node* n) {
  if (n == nullptr) {
    return nullptr;
  } else {
    return &(n->value);
  }
}

int* Sorted_list::first() {
  return Node::value_or_null(_first);
}

int* Sorted_list::last() {
  return Node::value_or_null(_sentinel->previous);
}

bool Sorted_list::is_empty() {
  return first() == nullptr;
}

void Sorted_list::update_first() {
  // loop backwards
  for (Node* n = _sentinel; n != nullptr; n = n->previous) {
    _first = n;
  }
}

void Sorted_list::Node::connect(Sorted_list::Node* a, Sorted_list::Node* b) {
  if (a == nullptr || a->value < b->value) {
    if (a != nullptr) {
      a->next = b;
    }
    if (b != nullptr) {
      b->previous = a;
    }
  } else {
    connect(b, a);
  }
}

/*void Sorted_list::insert(Sorted_list::Node* before, Sorted_list::Node* n, Sorted_list::Node* after) {
  Node::connect(before, n);
  Node::connect(n, after);
  update_first();
}*/

/*void Sorted_list::insert(Sorted_list::Node* before, int n, Sorted_list::Node* after) {
  Sorted_list::Node* nn = new Sorted_list::Node{};
  nn->value = n;
  insert(after, nn, before);
}*/

Sorted_list::Node* Sorted_list::insert(int n, Sorted_list::Node* a, Sorted_list::Node* b) {
  if (a == nullptr || a->value < b->value) {
    Sorted_list::Node* nn{};
    nn->value = n;

    Node::connect(a, nn);
    Node::connect(nn, b);

    update_first();

    return nn;
  } else {
    return insert(n, b, a);
  }
}

void Sorted_list::add(int n) {
  if (is_empty()) {
    _first = insert(n, nullptr, _sentinel);

    return;
  }
  for (auto it = _first; it != _sentinel; it = it->next) {
    if (it->value > n || it == _sentinel) {
      insert(n, it, it->previous);
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
  for (auto it = _first; it != _sentinel; it = it->next) {
    if ( it->value == n ) {

      Node::connect(it->previous, it->next);

      update_first();

      delete it;

      return;
    }
  }
}

int* Sorted_list::operator[](int i) {
  int j = 0;
  for (auto n = _first; n != _sentinel; n = n->next) {
    if (j++ == i) {
      return &(n->value);
    }
  }

  return nullptr;
}

std::ostream& operator<<(ostream& os, Sorted_list sl) {
  if (!sl.is_empty()) {
    os << sl.first();
    bool one_element = sl.first() == sl.last();
    if (!one_element) {
      // Eftersom node måste vara private blir det den här långsamma loopen istället :/
      for (int i = 0;; i++) {
        if (sl[i] == nullptr) {
          break;
        }
        os << ',' << sl[i];
      }
    }
  }

  return os;
}

string Sorted_list::to_string() {
  stringstream ss{};
  ss << (*this);

  return ss.str();
}
