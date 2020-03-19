#include "circuit.h"
#include <iomanip>

using namespace std;

void print_top(vector<Component*> & net) {
	// Rad 1.
   	for (Component* c : net) {
		for (uint32_t i = 0; i < 12 - c->get_name().length(); i++) {
			std::cout << ' ';
		}
		std::cout << c->get_name();
	}
	std::cout << '\n';
	// Rad 2.
	for (long long unsigned int i = 0; i < net.size(); i++) {
		cout << "  Volt  Curr";
	}
	std::cout << '\n';
}

void print(vector<Component*> & net) {
	std::cout << " ";
	for (Component* c : net) {
		std::cout << *c;
	}
	std::cout << "\n";
}

void simulate(vector<Component*> & net, int iterations, int prints, /*double battery_voltage,*/ double delta_t) {
	print_top(net);

	// set battery voltage

        // TODO: Detta känns bakvänt. Det är bättre att sätta
        // batteriets volt när man skapar batteriet.
	/*for (Component* c : net) {
		Battery* bat = dynamic_cast<Battery*> (c);
		if (bat != nullptr) {
			bat->_voltage = battery_voltage;
		}
	}*/

	int j = 0;
	for (int i = 0; i < iterations; i++ ) {
		if ((iterations / prints) * j <= i) {
			j++;
			print(net);
		}

		for (Component* c : net) {
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

double Component::get_voltage() const {
	return abs(_from.Potential - _to.Potential);
}

std::string Component::get_name() {
	return _name;
}

ostream& operator<<(ostream& os, Component const& c) {
	os
		<< std::setfill(' ') << std::setw(5) << std::right << std::fixed << std::setprecision(2)
		<< c.get_voltage()
		<< " "
		<< std::setfill(' ') << std::setw(5) << std::right << std::fixed << std::setprecision(2)
		<< c.get_current() << " ";

	return os;
}


Battery::Battery(std::string name, double voltage, Connection& from, Connection& to)
	: Component::Component(name, from, to), _voltage{ voltage } {}

Battery::~Battery() {}

double Battery::get_current() const {
	return 0;
}

void Battery::simulate(double) {
	_from.Potential = 0;
	_to.Potential = _voltage;
}


Resistor::Resistor(std::string name, double resistance, Connection& from, Connection& to)
	: Component::Component(name, from, to), _resistance{ resistance } {}

Resistor::~Resistor() {}

double Resistor::get_current() const {
	return get_voltage() / _resistance;
}

void Resistor::simulate(double delta_t) {
	move_potential(get_current() * delta_t, _from, _to);
}


Capacitor::Capacitor(std::string name, double capacitance, double charge, Connection& from, Connection& to)
	: Component::Component(name, from, to), _capacitance{ capacitance }, _charge{ charge } {}

Capacitor::~Capacitor() {}

double Capacitor::get_current() const {
	return _capacitance * (get_voltage() - _charge);
}

void Capacitor::simulate(double delta_t) {
	double x = get_current() * delta_t;
	move_potential(x, _from, _to);
	_charge += x;
}
