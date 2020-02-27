#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

class Sorted_list {
private:
  struct Node {
  public:
    int value;
    Node* next;
    Node* previous;

    //Node(int val);

    // static pga n kan vara nullptr
    static int* value_or_null(Node* n);

    // länkar ihop 2 noder
    static void connect(Node* a, Node* b);

    static Node* new_sentinel();
  };

  // länkar 3 noder
  //void insert(Node* before, Node* n, Node* after);
  // sätter n mellan a och b. returnerar n:s nod.
  Node* insert(int n, Node* a, Node* b);

  Node* _first; // första noden. == nullptr om listan är tom
  Node* _sentinel; // sista noden

  void update_first(); // sätt _first till första noden.
public:
  bool is_empty();

  // nullptr om tom
  int* first();// första värdet (nullptr om listan är tom)
  int* last(); // sista värdet

  bool contains(int n);

  void add(int n);
  void remove(int n);
  void remove_at_index(int i);

  void clear(); // töm listan

  int operator[](int i) const;

  int size() const;

  Sorted_list(std::initializer_list<int> l);
  // Kopiering.
  Sorted_list(Sorted_list const & that) noexcept;
  Sorted_list& operator=(Sorted_list const & that);
  // Tilldelning.
  Sorted_list(Sorted_list && that);
  Sorted_list& operator=(Sorted_list && that);
  // Destructor.
  ~Sorted_list();

  std::string to_string();
};

std::ostream& operator<<(std::ostream& os, Sorted_list sl);
