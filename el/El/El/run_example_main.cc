#include "Implementation.cc"
#include <sstream>

using namespace std;

struct simulation_params {
	int iterations;
	int prints;
	double delta_t;
	double bat_voltage;

	simulation_params(int argc, char* argv[]) {
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
	}

	void simulate_then_delete(vector<Component*> & net) {
		simulate(net, iterations, prints, bat_voltage, delta_t);

		for (auto c : net) {
			delete c;
		}
	}
};

void example_1(simulation_params params) {
	Connection P{};
	Connection N{};
	Connection Q_124{};
	Connection Q_23{};

	vector<Component*> net{};

	net.push_back(new Battery("U", N, P));

	net.push_back(new Resistor("R2", 4, Q_124,	Q_23));
	net.push_back(new Resistor("R1", 6, P,		Q_124));
	net.push_back(new Resistor("R3", 8, Q_23,	N));
	net.push_back(new Resistor("R4", 12,Q_124,	N));

	params.simulate_then_delete(net);
}

int main(int argc, char* argv[]) {
	cout << cout.precision(5) << cout.width(10) << 1.234567890 << '\n';

	example_1(simulation_params(argc, argv));
}