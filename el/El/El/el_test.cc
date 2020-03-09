#include <string>
#include <iostream>
#include <sstream>

#include "catch.hpp"
#include "header.h"

using namespace std;

// här lägger ni era testfall.
// Jobba enligt TDD;
//  1. Lägg till testfall
//  2. Testa
//  3. Lägg till (minsta möjliga) implementation
//  4. Testa alla testfall
//  5. Refaktorera (skriv om) så att allt ser bra ut

#if 01

TEST_CASE("Voltage") {
	Connection a{};
	Connection b{};
	a.Potential = -2;
	b.Potential = 3.5;

	Resistor* r = new Resistor("", 1, a, b);

	CHECK(r->get_voltage() == 5.5);

	delete r;
}

TEST_CASE("Battery") {
	Connection a{};
	Connection b{};

	vector<Component*> net{};

	Battery* bat = new Battery{ "bat", 10, a, b };

	CHECK(a.Potential == 0);
	CHECK(b.Potential == 0);
	CHECK(bat->get_current() == 0);
	CHECK(bat->get_voltage() == 0);

	bat->simulate(0.5);

	CHECK(a.Potential == 0);
	CHECK(b.Potential == 10);
	CHECK(bat->get_current() == 0);
	CHECK(bat->get_voltage() == 10);

	delete bat;
}

TEST_CASE("Resistor") {
	Connection a{};
	Connection b{};

	Battery* bat = new Battery{ "bat", 10, a, b };

	CHECK(a.Potential == 0);
	CHECK(b.Potential == 0);
	CHECK(bat->get_current() == 0);
	CHECK(bat->get_voltage() == 0);

	bat->simulate(0.5);

	CHECK(a.Potential == 0);
	CHECK(b.Potential == 10);
	CHECK(bat->get_current() == 0);
	CHECK(bat->get_voltage() == 10);

	delete bat;
}

TEST_CASE("Capacitor") {
	Connection a{};
	Connection b{};
	a.Potential = 5;
	b.Potential = 9;

	Capacitor* x = new Capacitor{ "component", 0.8, 0, a, b };

	CHECK(a.Potential == 5);
	CHECK(b.Potential == 9);
	CHECK(x->get_current() == 2);
	CHECK(x->get_voltage() == 4);

	x->simulate(0.1);

	CHECK(a.Potential == 5.8);
	CHECK(b.Potential == 8.2);
	CHECK(x->_charge == 0.8);
	CHECK(x->get_current() == 1.28);
	CHECK(x->get_voltage() == 2.4);

	delete x;
}

TEST_CASE("Circuit") {

}
#endif
