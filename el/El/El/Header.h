#pragma once

class Connection {

};

class Component {
	Connection _from;
	Connection _to;

	Component(Connection from, Connection to) : _from{ from }, _to{ to } {

	}
};

class Resistor : public Component {

};

class Battery : public Component {

};

class Capacitor : public Component {

};