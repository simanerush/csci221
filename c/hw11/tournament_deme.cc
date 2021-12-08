#include "tournament_deme.hh"
#include <cassert>

const size_t TOURNAMENT_SIZE = 256;


Chromosome *TournamentDeme::select_parent() {
	auto permutation = random_permutation(pop_.size());
	std::shuffle(permutation.begin(), permutation.end(), generator_);
	// Get first 256 cities
	permutation.resize(TOURNAMENT_SIZE);

	while (permutation.size() > 1) {
		assert(permutation.size() % 2 == 0);
		for (size_t i = 0; i < permutation.size(); i+=2) {
			auto a = permutation[i];
			auto b = permutation[i + 1];

			auto a_fitness = fitnesses_[a];
			auto b_fitness = fitnesses_[b];

			permutation[i / 2] = a_fitness > b_fitness ? permutation[i] : permutation[i + 1];
		}

		permutation.resize(permutation.size() / 2);
	}
	return pop_[permutation[0]];
}