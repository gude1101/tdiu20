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

TEST_CASE("First & last") {
    Sorted_list sl{1, 6000, -200, 3};
    CHECK(*sl.first() == -200);
    CHECK(*sl.last() == 6000);
}

TEST_CASE("Add & remove") {
    Sorted_list sl{1, 6000, -200, 3};

    sl.add(-300);
    CHECK(*sl.first() == -300);

    sl.remove(3);
    CHECK(sl.to_string() == "[-300, -200, 1, 6000]");
}
#endif
