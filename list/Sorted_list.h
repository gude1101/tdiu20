class Sorted_list {
public:
  Sorted_list(int const items...) {}
private:
  class Node {
    int value;
    Node* next;
  };
  Node _first;
  Node _last;
};
