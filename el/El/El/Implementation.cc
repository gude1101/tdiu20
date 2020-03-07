#include "Header.h"

using namespace std;

Component::Component(std::string name, double special_val, Connection from, Connection to)
	: _name{ name }, _special_val{ special_val }, _from{ from }, _to{ to } {}

double Component::get_voltage() {
	return _from.Potential - _to.Potential;
}

ostream operator<<(ostream& os, Component& c) {
	os
		<< cout.width(5) << cout.precision(2)
		<< c.get_voltage() << " " << c.get_current();
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
	double x = _to.Potential - _from.Potential;
	x /= _special_val;
	x *= delta_t;

	_to.Potential += x;
	_from.Potential -= x;
}


double Capacitor::get_current() {
	return _special_val * (get_voltage() - _charge);
}

void Capacitor::simulate(double delta_t) {
	double x = get_current() * delta_t;
	_from.Potential -= x;
	_charge += x;
	_to.Potential += x;
}