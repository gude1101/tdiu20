#include "Header.h"

Component::Component(std::string name, double special_val, Connection from, Connection to)
	: _name{ name }, _special_val{ special_val }, _from{ from }, _to{ to } {}

void Battery::simulate() {
	_from.Potential = 0;
	_to.Potential = _special_val;
}

void Resistor::simulate() {
	double voltage = (_to.Potential - _from.Potential) * 
}