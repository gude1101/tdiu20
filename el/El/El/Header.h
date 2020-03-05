#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>

void simulate(std::vector<Component*> net, int iterations, double voltage, double delta_t);

class Connection {
public:
	double Potential;
};

class Component {
protected:
	std::string _name;
	double _special_val;
	Connection _from;
	Connection _to;
public:
	Component(std::string name, double special_val, Connection from, Connection to);

	virtual void simulate() = 0; // abstract
};

class Battery : public Component {
	using Component::Component;
	void simulate();
};

class Resistor : public Component {
	using Component::Component;
	void simulate();
};

class Capacitor : public Component {
	using Component::Component;
	void simulate();
};