#include <iostream>
#include <sstream>
#include <string>

class Sorted_list {
public:
  struct Node {
    int value;
    Node* next;
    Node* previous;
  };

  Node* first();
  Node* last();

  void add(int n);
  void remove(int n);

  // TODO
  //int operator[](int i);

  //Sorted_list();
  Sorted_list(std::initializer_list<int> l);

  std::string to_string();
private:
  Node* _first;
  Node* _sentinel;
};

std::ostream& operator<<(std::ostream& os, Sorted_list sl);
