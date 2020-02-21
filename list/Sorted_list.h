#include <iostream>
#include <sstream>
#include <string>

class Sorted_list {
private:
  struct Node {
  public:
    int value;
    Node* next;
    Node* previous;

    // static pga n kan vara nullptr
    static int* value_or_null(Node* n);

    // länkar 2 noder
    static void connect(Node* a, Node* b);
  };

  // länkar 3 noder
  //void insert(Node* before, Node* n, Node* after);
  // sätter n mellan a och b. returnerar n:s nod.
  Node* insert(int n, Node* a, Node* b);

  Node* _first;
  Node* _sentinel; // sista noden

  void update_first();
public:
  bool is_empty();

  // nullptr om tom
  int* first();// första värdet (nullptr om listan är tom)
  int* last(); // sista värdet

  void add(int n);
  void remove(int n);

  int* operator[](int i);

  Sorted_list(std::initializer_list<int> l);

  std::string to_string();
};

std::ostream& operator<<(std::ostream& os, Sorted_list sl);
