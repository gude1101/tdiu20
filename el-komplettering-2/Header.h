#pragma once

#ifndef Header
#define Header

#define abstract 0

#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>

// TODO: Ni ska ha rimliga namn på filerna. Tex components.h och
// components.cc.

// TODO: Eran kod kompilerar med varningar. Kompilera med följande
// kommando för att se detta: g++ -std=c++17 -Wpedantic -Wall -Wextra

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
	virtual double get_current() = 0;
	double get_voltage();

	std::string get_name();
};

void simulate(std::vector<Component*> & net, int iterations, int prints, double battery_voltage, double delta_t);

std::ostream& operator<<(std::ostream & os, Component & c);

class Battery : public Component {
private:
	double _voltage = 0;
public:
    //using Component::Component;
	Battery(std::string name, double voltage, Connection& from, Connection& to);
	~Battery();

   // TODO: Funktioner som skriver över ska vara deklarerade med
   // override. Gäller i alla klasser
	override void simulate(double delta_t);
	override double get_current();
};

class Resistor : public Component {
protected:
	double _resistance;
public:
	Resistor(std::string name, double resistance, Connection& from, Connection& to);
	~Resistor();

	override void simulate(double delta_t);
	override double get_current();
};

class Capacitor : public Component {
protected:
	double _capacitance;
public:
	double _charge;

	Capacitor(std::string name, double capacitance, double charge, Connection& from, Connection& to);
	~Capacitor();

	override void simulate(double delta_t);
	override double get_current();
};

#endif
