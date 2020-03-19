#pragma once

#ifndef Header
#define Header

#define abstract 0

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
	virtual ~Component() = default;

	virtual void simulate(double delta_t) = 0;
	virtual double get_current() const = 0;
	double get_voltage() const;

	std::string get_name();
};

void simulate(std::vector<Component*> & net, int iterations, int prints, /*double battery_voltage,*/ double delta_t);

std::ostream& operator<<(std::ostream & os, Component const & c);

class Battery : public Component {
private:
	double _voltage = 0;
public:
    //using Component::Component;
	Battery(std::string name, double voltage, Connection& from, Connection& to);
	~Battery();

	void simulate(double) override;
	double get_current() const override;
};

class Resistor : public Component {
private:
	double _resistance;
public:
	Resistor(std::string name, double resistance, Connection& from, Connection& to);
	~Resistor();

	void simulate(double delta_t) override;
	double get_current() const override;
};

class Capacitor : public Component {
private:
	double _capacitance;
public:
	double _charge;

	Capacitor(std::string name, double capacitance, double charge, Connection& from, Connection& to);
	~Capacitor();

	void simulate(double delta_t) override;
	double get_current() const override;
};

#endif
