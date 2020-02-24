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

#if 1
TEST_CASE("Stuff")
{
    Sorted_list sl = Sorted_list{};
    CHECK(sl.to_string() == "");

    sl = Sorted_list{1, 6000, -200, 3};
    CHECK(sl.to_string() == "-200, 1, 3, 6000");

    CHECK(sl.first()->value == -200);
    CHECK(sl.last()->value == 6000);

    sl.add(-300);
    CHECK(sl.first()->value == -300);

    sl.remove(3);
    CHECK(sl.to_string() == "-300, -200, 1, 6000");
}
#endif
