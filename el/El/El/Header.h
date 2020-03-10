#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>

class Connection {
public:
	double Potential = 0;
};

class Component {
protected:
	std::string _name;
	Connection & _from;
	Connection & _to;
public:
	Component(std::string name, Connection & from, Connection & to);

	virtual void simulate(double delta_t) = 0;
	virtual double get_current() = 0;
	double get_voltage();

	std::string get_name();
};

void simulate(std::vector<Component*> net, int iterations, int prints, double battery_voltage, double delta_t);

std::ostream& operator<<(std::ostream & os, Component & c);

class Battery : public Component {
public:
	double _voltage;

	using Component::Component;
	void simulate(double delta_t);
	double get_current();
};

class Resistor : public Component {
protected:
	double _resistance;
public:
	Resistor(std::string name, double resistance, Connection& from, Connection& to);

	void simulate(double delta_t);
	double get_current();
};

class Capacitor : public Component {
protected:
	double _capacitance;
public:
	double _charge;

	Capacitor(std::string name, double capacitance, double charge, Connection& from, Connection& to);

	void simulate(double delta_t);
	double get_current();
};