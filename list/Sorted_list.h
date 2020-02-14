#include <iostream>

//#define abstract 0

class Sorted_list {
public:
  struct Node {
    int value;
    Node* next;
  };

  Sorted_list(int const items...) {};

  Node* first();
  Node* last();

  void add(int n);
  void remove(int n);

private:  
  Node* _first;
  Node* _last;
  
};

std::ostream operator<<(std::ostream & os, Sorted_list & sl);
