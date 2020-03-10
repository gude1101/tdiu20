#include "Implementation.cc"
#include <sstream>

using namespace std;

vector<Component*> & example_1() {
	Connection P{};
	Connection N{};
	Connection Q_124{};
	Connection Q_23{};
	
	vector<Component*> net{};

	net.push_back(new Resistor("R2", 4, Q_124, Q_23));
	net.push_back(new Resistor("R1", 6, P, Q_124));
	net.push_back(new Resistor("R3", 8, Q_23, N));
	net.push_back(new Resistor("R4", 12, Q_124, N));

	return net;
}

int main(int argc, char* argv[]) {
	int iterations;
	int prints;
	double delta_t;
	double bat_voltage;

	if (argc > 0 && false) {
		stringstream ss{};
		for (int i = 0; i < argc; i++) {
			ss << *(argv[i]);
		}
		ss >> iterations;
		ss >> prints;
		ss >> delta_t;
		ss >> bat_voltage;
	}
	else {
		iterations = 200000;
		prints = 10;
		delta_t = 0.01;
		bat_voltage = 24;
	}

	auto x = example_1();

	simulate(x, iterations, prints, bat_voltage, delta_t);

	for (auto c : x) {
		delete c;
	}
}