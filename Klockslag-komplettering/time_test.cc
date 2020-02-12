#include <string>
#include <iostream>
#include <sstream>

#include "catch.hpp"
#include "Time.h"

using namespace std;

// här lägger ni era testfall.
// Jobba enligt TDD;
//  1. Lägg till testfall
//  2. Testa
//  3. Lägg till (minsta möjliga) implementation
//  4. Testa alla testfall
//  5. Refaktorera (skriv om) så att allt ser bra ut

TEST_CASE ("Default constructor")
{
    Time t;

    CHECK(t.hour() == 0);
    CHECK(t.minute() == 0);
    CHECK(t.second() == 0);
}

// the following line will halt the compilation process. Move it
// one test case at the time and then start creating your own test
// cases
//#if 0
TEST_CASE ( "Constructor with numeric arguments" )
{
    Time t{12,13,14};
    CHECK(t.hour() == 12);
    CHECK(t.minute() == 13);
    CHECK(t.second() == 14);
}

//#if 0
TEST_CASE ("Constructor with faulty argument")
{
    CHECK_THROWS( Time{41,0,0} );
    CHECK_THROWS( Time{0,99,0} );
    CHECK_THROWS( Time{0,0,99} );
}

//#if 0
TEST_CASE ("String constructor")
{
    Time t{"12:23:12"};
    CHECK(t.hour() == 12);
    CHECK(t.minute() == 23);
    CHECK(t.second() == 12);

    SECTION ("Throws as well")
    {
        CHECK_THROWS( Time{"02:11:74"} );
    }
}

TEST_CASE ("am or pm")
{
    Time t{12,12,31};
    CHECK_FALSE(t.is_am());
    Time t2{1,2,3};
    CHECK(t2.is_am());
}

//#if 0
TEST_CASE ("Convert to string" )
{
    CHECK( Time{12,12,12}.to_string()     ==    "12:12:12" );
    CHECK( Time{12, 1, 2}.to_string()     ==    "12:01:02" );
    CHECK( Time{14,33,12}.to_string(true) == "02:33:12 pm" );
}

//#if 01
TEST_CASE ("Conversion to string" )
{
    CHECK( string(Time{2,4,1}) == "02:04:01" );
}

//TODO: Testa också att +/- operatorn klarar av sekunder > 86400 (över en dag).
TEST_CASE ("Plus / minus") {
    CHECK((Time{10, 10, 10} + 86460).to_string() == "10:11:10");
    CHECK((Time{12, 12, 12} + 3600).to_string() == "13:12:12");
    CHECK((Time{12, 12, 12} + 61).to_string() == "12:13:13");
    CHECK((Time{12, 12, 12} + 1).to_string() == "12:12:13");
    CHECK((Time{12, 10, 9} - 61).to_string() == "12:09:08");

    CHECK(++Time{12,59,59} == Time{13, 00, 00});
    CHECK(--Time{12,00,00} == Time{11, 59, 59});

    Time t = Time{1, 1, 59};
    t++;
    CHECK(t == Time{1, 2, 0});
    t--;
    CHECK(t == Time{1, 1, 59});

    CHECK((Time{12, 10, 9}--) == Time{12, 10, 9});
    CHECK((Time{12, 10, 9}++) == Time{12, 10, 9});
}

TEST_CASE ("< >") {
  CHECK(Time{10, 10, 9} < Time {10, 10, 10});
  CHECK(Time{9, 10, 10} > Time{8, 9, 9});
  CHECK(Time{1,1,1} == Time{1,1,1});
}

#if 01
TEST_CASE ("Output operator" )
{
    stringstream ss;
    SECTION("Simple output")
    {
        ss << Time{2,5,1};
        CHECK(ss.str() == "02:05:01");
    }
    SECTION("Chained output")
    {
        ss << Time{23,10,32} << "---";
        CHECK(ss.str() == "23:10:32---");
    }
    SECTION("Const time")
    {
        Time const t{23,23,23};
        ss << t;
        CHECK(ss.str() == "23:23:23");
    }
}

//TODO: Här ska ni också testa så att failflaggan sätts.
// (Se kommentaren till input operatorn).
//TODO: Ni ska också testa så att chained input fungerar.
TEST_CASE ("Input operator") {
  stringstream ss;
  ss << "12:12:12";
  Time t;
  ss >> t;
  CHECK(t.to_string() == "12:12:12");

  SECTION ("Chained input") {
      stringstream ss;
      int n;
      float f;
      ss << "5 12:12:12 3.14";
      CHECK(ss.str() == "5 12:12:12 3.14");
      ss >> n >> t >> f;
      CHECK(n == 5);
      CHECK(t.to_string() == "12:12:12");
      CHECK(f == 3.14f);
  }

  SECTION("Fail flag") {
    CHECK(ss.fail() == false);
    ss << "12:12:60";
    ss >> t;
    CHECK(ss.fail() == true);
  }
}
#endif
