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
	a.Potential = 5;
	b.Potential = 9;

	Resistor* x = new Resistor{ "res", 2, a, b };

	CHECK(x->get_current() == 4 / 2);
	
	x->simulate(0.1);

	CHECK(a.Potential == 5 + (4.0/2.0)*0.1);
	CHECK(b.Potential == 9 - (4.0/2.0)*0.1);
}

TEST_CASE("Capacitor") {
	Connection a{};
	Connection b{};
	a.Potential = 5;
	b.Potential = 9;

	Capacitor* x = new Capacitor{ "component", 0.8, 3, a, b };

	CHECK(x->get_current() == 0.8);

	x->simulate(0.1);

	CHECK(a.Potential == 5 + (0.8 * (4.0 - 3.0) * 0.1));
	CHECK(b.Potential == 9 - (0.8 * (4.0 - 3.0) * 0.1));
	CHECK(x->_charge == 3 + (0.8 * (4.0 - 3.0) * 0.1));

	delete x;
}

TEST_CASE("Circuit") {

}
#endif
