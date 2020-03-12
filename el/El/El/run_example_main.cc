#include "Implementation.cc"
#include <sstream>
#include <stdexcept>

using namespace std;

class simulation_params {
private:
	int iterations;
	int prints;
	double delta_t;
	double bat_voltage;
public:

	simulation_params() {
		iterations = 200000;
		prints = 10;
		delta_t = 0.01;
		bat_voltage = 24;
	}

	simulation_params(int argc, char* argv[]) {
		if (argc < 4) {
			throw std::invalid_argument("Too few arguments.");
		}
		if (argc > 4) {
			throw std::invalid_argument("Too many arguments.");
		}

		stringstream ss{};
		for (int i = 0; i < argc; i++) {
			ss << *(argv[i]);
		}
		ss >> iterations;
		if (ss.fail()) {
			throw invalid_argument("iterations");
		}
		ss >> prints;
		if (ss.fail()) {
			throw invalid_argument("prints");
		}
		ss >> delta_t;
		if (ss.fail()) {
			throw invalid_argument("delta t");
		}
		ss >> bat_voltage;
		if (ss.fail()) {
			throw invalid_argument("battery voltage");
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

	net.push_back(new Battery("Bat", N, P));

	net.push_back(new Resistor("R1", 6, P,		Q_124));
	net.push_back(new Resistor("R2", 4, Q_124,	Q_23));
	net.push_back(new Resistor("R3", 8, Q_23,	N));
	net.push_back(new Resistor("R4", 12,Q_124,	N));

	params.simulate_then_delete(net);
}

void example_2(simulation_params p) {
	Connection P{};
	Connection N{};
	Connection L{};
	Connection R{};

	vector<Component*> net{};

	net.push_back(new Battery("U", N, P));

	net.push_back(new Resistor("R1", 150, P, L));
	net.push_back(new Resistor("R2", 50, P, R));
	net.push_back(new Resistor("R3", 100, L, R));
	net.push_back(new Resistor("R4", 300, L, N));
	net.push_back(new Resistor("R5", 250, R, N));

	p.simulate_then_delete(net);
}

void example_3(simulation_params p) {
	Connection P{};
	Connection N{};
	Connection L{};
	Connection R{};

	vector<Component*> net{};

	net.push_back(new Battery("U", N, P));

	net.push_back(new Resistor("R1", 150, P, L));
	net.push_back(new Resistor("R2", 50, P, R));
	net.push_back(new Capacitor("C3", 1.0, 0, L, R));
	net.push_back(new Resistor("R4", 300, L, N));
	net.push_back(new Capacitor("C5", 0.75, 0, R, N));

	p.simulate_then_delete(net);
}

int main(int argc, char* argv[]) {
	simulation_params params{argc, argv};

	example_1(params);
	cout << '\n';
	example_2(params);
	cout << '\n';
	example_3(params);
}