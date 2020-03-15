#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <algorithm>

class Sorted_list {
private:

  struct Node {

  public:
    int value;
    Node* next;
    Node* previous;

    // static pga n kan vara nullptr
    // returnerar nullptr om n är nullptr
    static int const * value_or_null(Node const * const n);

    static bool is_in_order(Node const * const a, Node const * const b);

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

  bool is_empty() const;

  // nullptr om tom
  int const * first() const;// första värdet (nullptr om listan är tom)
  int const * last() const; // sista värdet

  bool contains(int n);

  void add(int n);
  void remove(int n);
  void remove_at_index(int i);

  void clear(); // töm listan

  int operator[](int i) const;

  int size() const;

  Sorted_list(std::initializer_list<int> l);
  // Kopiering.
  Sorted_list(Sorted_list const & that);
  Sorted_list& operator=(Sorted_list const & that);
  // Flytt.
  Sorted_list(Sorted_list && that);
  Sorted_list& operator=(Sorted_list && that);
  // Destructor.
  ~Sorted_list();

  std::string to_string() const;

  // Kollar att listorna inte delar någon nod, och att sentinel är sist.
  static bool test_for_no_connection(Sorted_list const& a, Sorted_list const& b);
};

std::ostream& operator<<(std::ostream& os, Sorted_list const & sl);
