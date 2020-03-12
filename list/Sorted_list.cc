#include "Sorted_list.h"

using namespace std;

#ifndef INT_MAX
#define INT_MAX 2147483647
#endif


Sorted_list::Sorted_list(std::initializer_list<int> il) : _first{nullptr}, _sentinel{new Node{}} {
  _sentinel->previous = _first;
  _sentinel->next = nullptr;
  _sentinel->value = INT_MAX;

  for (int e : il) {
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

//Sorted_list::Node::Node(int val) : value{val}, next{nullptr}, previous{nullptr} {}

Sorted_list::Node* Sorted_list::Node::new_sentinel() {
  Node* n = new Node{};
  n->value = INT_MAX;
  return n;
}

Sorted_list::Sorted_list(Sorted_list const & that) : _first{nullptr}, _sentinel{Node::new_sentinel()} {
  *this = that;
}

Sorted_list& Sorted_list::operator=(Sorted_list const & that) {
  clear();
  for (int i = 0; i < that.size(); i++) {
    add(that[i]);
  }

  return *this;
}

Sorted_list::Sorted_list(Sorted_list && that) : Sorted_list{} {
  *this = std::move(that);
}

Sorted_list& Sorted_list::operator=(Sorted_list && that) {
  Node* temp = _first;
  _first = that._first;
  that._first = temp;

  temp = _sentinel;
  _sentinel = that._sentinel;
  that._sentinel = temp;

  return *this;
}

Sorted_list::~Sorted_list() {
  clear();
  delete _sentinel; // OBS! Glöm inte! Här var minnesläckan.
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
  _first = nullptr;
  for (Node* n = _sentinel->previous; n != nullptr; n = n->previous) {
    _first = n;
  }
}

bool Sorted_list::Node::is_in_order(Sorted_list::Node* a, Sorted_list::Node* b) {
  if (b == nullptr) {
    return false;
  }
  if (a == nullptr) {
    return true;
  }
  return a->value <= b->value; // OBS! kan vara ==
}

void Sorted_list::Node::connect(Sorted_list::Node* a, Sorted_list::Node* b) {
  // Garantera storleksordning.
  if (!is_in_order(a, b)) {
    connect(b, a); // Byter ordning på a och b.

    return;
  }

  if (a != nullptr) {
    a->next = b;
  }
  if (b != nullptr) {
    b->previous = a;
  }
}

Sorted_list::Node* Sorted_list::insert(int n, Sorted_list::Node* a, Sorted_list::Node* b) {
  // Garantera storleksordning.
  if (!Node::is_in_order(a, b)) {
    return insert(n, b, a); // Byter ordning på a och b.
  }

  Sorted_list::Node* nn = new Node{};
  nn->value = n;

  Node::connect(a, nn);
  Node::connect(nn, b);

  update_first();

  return nn;
}

bool Sorted_list::contains(int n) {
  for (Node* it = _first; it != nullptr; it = it->next) {
    if (it->value == n) {
      return true;
    }
  }
  return false;
}

void Sorted_list::add(int n) {
  if (is_empty()) {
    _first = insert(n, nullptr, _sentinel);

    // Ingen loop krävs.
    return;
  }
  for (auto it = _first;; it = it->next) {
    if (it->value > n || it == _sentinel) {
      insert(n, it, it->previous);

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

void Sorted_list::remove_at_index(int i) {
  remove((*this)[i]);
}

void Sorted_list::clear() {
  while(!is_empty()) {
    remove(*first());
  }
}

int Sorted_list::operator[](int i) const {
  int j = 0;
  for (auto n = _first; n != _sentinel; n = n->next) {
    if (j++ == i) {
      return n->value;
    }
  }

  throw out_of_range{"i"};
}

int Sorted_list::size() const {
  int i{};
  for (auto it = _first; it != _sentinel; it = it->next) {
    i++;
  }
  return i;
}

std::ostream& operator<<(ostream& os, Sorted_list sl) {
  os << sl.to_string();
  return os;
}

string Sorted_list::to_string() {
  stringstream ss{};

  ss << '[';

  if (!is_empty()) {
    ss << *first();
    bool one_element = first() == last();
    // Bara kommatecken om fler än ett element
    if (!one_element) {
      for (auto it = _first->next; it != _sentinel; it = it->next) {
        ss << ", " << it->value;
      }
    }
  }

  ss << ']';

  return ss.str();
}
