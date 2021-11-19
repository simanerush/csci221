
#include <string>
#include <cmath>
#include <numeric>
#include <random>
#include <sstream>
#include <string>

#include "cities.hh"


Cities Cities::reorder(const permutation_t& ordering) const {
	assert(ordering.size() == coords.size());
	Cities res = {};

	// Push coords in order of reordering
	for (const auto index : ordering) {
		res.push_city(coords[index]);
	}

	return res;
}

double Cities::total_path_distance(const permutation_t& ordering) const {
	assert(ordering.size() == coords.size());
	double res = 0.0;
	for (size_t i = 0; i < ordering.size(); i++) {
		const auto first = ordering[i];

		// Every pair, if end, match with the first element
		const auto second = ordering[(i + 1) % ordering.size()];

		const auto& coord_a = coords[first];
		const auto& coord_b = coords[second];

		auto del_y = double(coord_a.second) - double(coord_b.second);
		auto del_x = double(coord_a.first) - double(coord_b.first);

		res += std::hypot(del_x, del_y);
	}

	return res;
}

// Helper method to push coords to coords vector
void Cities::push_city(coord_t coord) {
	coords.push_back(coord);
}

std::istream& operator >> (std::istream& stream, Cities& cities) {
	std::string line;
	// Parse through each line in the file
	while (std::getline(stream, line)) {
		std::istringstream line_stream{line};
		Cities::coord_t coord;
		line_stream >> coord.first >> coord.second;
		cities.push_city(coord);
	}

	return stream;
}

std::ostream& operator << (std::ostream& stream, Cities& cities) {
	for (Cities::coord_t coord : cities.coords) {

		// Concatenate the coordinates into a tabulated string
		stream << coord.first << "\t" << coord.second << std::endl;
	}
	return stream;
}

// Use specified seed
Cities::permutation_t random_permutation(unsigned len, unsigned seed) {
	// To keep getting different random numbers
	std::default_random_engine engine{seed};
	Cities::permutation_t result(len);
	// Fill the result with increasing numbers
	std::iota(result.begin(), result.end(), 0);
	// Shuffle the vector
	std::shuffle(result.begin(), result.end(), engine);

	return result;
}

// Generate new seed every time
Cities::permutation_t random_permutation(unsigned len) {
	// Generate the new seed every time
	static unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	// To keep getting different random numbers
	static std::default_random_engine engine{seed};
	Cities::permutation_t result(len);
	// Fill the result with increasing numbers
	std::iota(result.begin(), result.end(), 0);
	// Shuffle the vector
	std::shuffle(result.begin(), result.end(), engine);

	return result;
}

size_t Cities::size() const {
	return coords.size();
}

