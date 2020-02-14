#include "Sorted_list.h"

using namespace std;

Sorted_list::Sorted_list(int const items...) : _first{&(Sorted_list::Node{})}, _last{_first} {

}

Sorted_list::first() {
    return _first;
}

Sorted_list::last() {
    return _last;
}

Sorted_list::remove(int n) {
    for (Sorted_list::Node* it =  sl.first(); it != sl.last(); it = (*it).next) {
        if (((*((*it).next)).value) == n) {
            (*it).next
        }
    }
}

ostream operator<<(ostream & os, Sorted_list & sl) {
    Sorted_list::Node* it = sl.first();
    os << (*it).value;
    for (it =  (*it).next; it != sl.last(); it = (*it).next) {
        os << ', ' << (*it).value;
    }
}