#pragma once

#ifndef Implementation
#define Implementation

#include "Header.h"

using namespace std;

void print_top(vector<Component*> & net) {
	for (auto c : net) {
		for (uint32_t i = 0; i <= 9 - c->get_name().length(); i++) {
			std::cout << ' ';
		}
		std::cout << c->get_name();
	}
	std::cout << '\n';
	for (auto c : net) {
		cout << " Volt Curr";
	}
	std::cout << '\n';
}

void print(vector<Component*> & net) {
	for (auto c : net) {
		std::cout << *c;
	}
	std::cout << "\n";
}

void simulate(vector<Component*> & net, int iterations, int prints, double battery_voltage, double delta_t) {
	print_top(net);

	// set battery voltage
	for (auto c : net) {
		Battery* bat = dynamic_cast<Battery*> (c);
		if (bat != nullptr) {
			bat->_voltage = battery_voltage;
		}
	}

	int j = 0;
	for (int i = 0; i < iterations; i++ ) {
		if ((iterations / prints) * j <= i) {
			j++;
			print(net);
		}

		for (auto c : net) {
			c->simulate(delta_t);
		}
	}
}

void move_potential(double amount, Connection& a, Connection& b) {
	if (a.Potential > b.Potential) {
		move_potential(amount, b, a);

		return;
	}
	a.Potential += amount;
	b.Potential -= amount;
}


Component::Component(std::string name, Connection& from, Connection& to)
	: _name{ name }, _from{ from }, _to{ to } {}

double Component::get_voltage() {
	return abs(_from.Potential - _to.Potential);
}

std::string Component::get_name() {
	return _name;
}

ostream& operator<<(ostream& os, Component& c) {
	os
		<< cout.width(5) << cout.precision(2)
		<< c.get_voltage() << " " << c.get_current();

	return os;
}


Battery::Battery(std::string name, double voltage, Connection& from, Connection& to)
	: Component::Component(name, from, to), _voltage{ voltage } {}

double Battery::get_current() {
	return 0;
}

void Battery::simulate(double delta_t = 0) {
	_from.Potential = 0;
	_to.Potential = _voltage;
}


Resistor::Resistor(std::string name, double resistance, Connection& from, Connection& to)
	: Component::Component(name, from, to), _resistance{ resistance } {}

double Resistor::get_current() {
	return get_voltage() / _resistance;
}

void Resistor::simulate(double delta_t) {
	move_potential(get_current() * delta_t, _from, _to);
}


Capacitor::Capacitor(std::string name, double capacitance, double charge, Connection& from, Connection& to)
	: Component::Component(name, from, to), _capacitance{ capacitance }, _charge{ charge } {}

double Capacitor::get_current() {
	return _capacitance * (get_voltage() - _charge);
}

void Capacitor::simulate(double delta_t) {
	double x = get_current() * delta_t;
	move_potential(x, _from, _to);
	_charge += x;
}

#endif