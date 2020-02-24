#include <string>
#include <iostream>
#include <sstream>

#include "catch.hpp"
#include "Sorted_list.h"

using namespace std;

// här lägger ni era testfall.
// Jobba enligt TDD;
//  1. Lägg till testfall
//  2. Testa
//  3. Lägg till (minsta möjliga) implementation
//  4. Testa alla testfall
//  5. Refaktorera (skriv om) så att allt ser bra ut

#if 01

TEST_CASE("Empty constructor")
{
    Sorted_list sl{};
    CHECK(sl.to_string() == "[]");
}

TEST_CASE("Long constructor") {
    Sorted_list sl{1, 6000, -200, 3};
    CHECK(sl.to_string() == "[-200, 1, 3, 6000]");
}

TEST_CASE("Size") {
  Sorted_list sl{1, 6000, -200, 3};
  CHECK(sl.size() == 4);
}

TEST_CASE("Add & remove") {
    Sorted_list sl{1, 6000, -200, 3};

    sl.add(-300);
    CHECK(*sl.first() == -300);
    sl.add(6000);
    CHECK(sl.to_string() == "[-300, -200, 1, 3, 6000, 6000]");

    sl.remove(3);
    CHECK(sl.to_string() == "[-300, -200, 1, 6000, 6000]");

    sl.remove_at_index(1);
    CHECK(sl.to_string() == "[-300, 1, 6000, 6000]");
}

TEST_CASE("Indexing") {
  Sorted_list sl{1, 6000, -200, 3};

  CHECK(sl[3] == 6000);
  CHECK(sl[2] == 3);
  CHECK(sl[1] == 1);
  CHECK(sl[0] == -200);
}

TEST_CASE("Out of range exception") {
    Sorted_list sl{1, 6000, -200, 3};
    CHECK_THROWS(sl[4]);
    CHECK_THROWS(sl[-1]);
    CHECK_THROWS(sl.remove_at_index(4));
    CHECK_THROWS(sl.remove_at_index(-1));
}

TEST_CASE("OStream") {
  Sorted_list sl{1, 6000, -200, 3};
  stringstream ss{};

  ss << "test " << sl << 3.14;

  CHECK(ss.str() == "test [-200, 1, 3, 6000]3.14");
}

/*TEST_CASE("Copy") {
  Sorted_list sl1{1, 6000, -200, 3};
  Sorted_list sl2{sl1};
  CHECK(sl1.to_string() == sl2.to_string());

  Sorted_list sl3{};
  sl3 = sl2;
  CHECK(sl3.to_string() == sl2.to_string());
}*/

TEST_CASE("Destructor") {
  Sorted_list* sl = new Sorted_list{1, 6000, -200, 3};
  delete sl;
  CHECK(sl == nullptr);
}
#endif
