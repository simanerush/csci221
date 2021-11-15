#include <fstream>
#include <iostream>

#include "cities.hh"

static const int ITERATIONS = 1000000;

int main(int argc, char* argv[]) {
	assert(argc >= 2);
	std::fstream fs{argv[1]};
	Cities cities {};
	fs >> cities;
	double distance = std::numeric_limits<double>::max();
	for (int i = 0; i < ITERATIONS; i++) {
		auto permutation = random_permutation(cities.size());
		auto dist = cities.total_path_distance(permutation);
		if (dist < distance) {
			distance = dist;
		}
	}
	std::cout << distance << std::endl;

	return 0;
}