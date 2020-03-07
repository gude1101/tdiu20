#include "Header.h"

using namespace std;

void simulate(vector<Component*> net, int iterations, int prints, double delta_t) {
	for (int i = 0; i < iterations; i++ ) {
		for (auto c : net) {
			c->simulate(delta_t);
		}
	}
}


Component::Component(std::string name, double special_val, Connection from, Connection to)
	: _name{ name }, _special_val{ special_val }, _from{ from }, _to{ to } {}

void move_potential(double amount, Connection& a, Connection& b) {
	if (a.Potential > b.Potential) {
		move_potential(amount, b, a);

		return;
	}
	a.Potential += amount;
	b.Potential -= amount;
}


double Component::get_voltage() {
	return abs(_from.Potential - _to.Potential);
}

ostream& operator<<(ostream& os, Component& c) {
	os
		<< cout.width(5) << cout.precision(2)
		<< c.get_voltage() << " " << c.get_current();

	return os;
}


double Battery::get_current() {
	return 0;
}

void Battery::simulate(double delta_t) {
	_from.Potential = 0;
	_to.Potential = _special_val;
}


double Resistor::get_current() {
	return get_voltage() / _special_val;
}

void Resistor::simulate(double delta_t) {
	move_potential(get_voltage() * delta_t, _from, _to);
}


double Capacitor::get_current() {
	return _special_val * (get_voltage() - _charge);
}

void Capacitor::simulate(double delta_t) {
	double x = get_current() * delta_t;
	move_potential(x, _from, _to);
	_charge += x;
}