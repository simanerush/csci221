#include "crossover.hh"

static void add_neighbors(std::vector<unsigned>& values, const std::vector<unsigned>& ordering, unsigned index) {
	auto before = index == 0 ? ordering.size() - 1 : index - 1;
	auto after = index == ordering.size() - 1 ? 0 : index + 1;

	if (std::find(values.begin(), values.end(), ordering[before]) != values.end()) {
		values.push_back(ordering[before]);
	}

	if (std::find(values.begin(), values.end(), ordering[after]) != values.end()) {
		values.push_back(ordering[after]);
	}
}

std::vector<unsigned> find_neighbors(const Chromosome *a, const Chromosome *b, unsigned neighbor) {
	auto& a_ordering = a->get_ordering();
	auto& b_ordering = b->get_ordering();

	const auto a_index = std::find(a_ordering.cbegin(), a_ordering.cend(), neighbor) - a_ordering.cbegin();
	const auto b_index = std::find(b_ordering.cbegin(), b_ordering.cend(), neighbor) - b_ordering.cbegin();

	std::vector<unsigned> neighbors{};

	add_neighbors(neighbors, a_ordering, a_index);
	add_neighbors(neighbors, b_ordering, b_index);

	return neighbors;

}

static std::vector<unsigned> lowest_neighbors(const Chromosome *a, const Chromosome *b, 
	const std::vector<unsigned> &neighbors) {

	std::vector<unsigned> result{};
	auto neighbor_count = std::numeric_limits<unsigned>::max();

	for (const auto& neighbor : neighbors) {
		auto count = find_neighbors(a, b, neighbor).size();
		if (count == neighbor_count) {
			result.push_back(neighbor);
		} else if (count < neighbor_count) {
			result = {neighbor};
			neighbor_count = count;
		}
	}

	return result;
}

template <typename RNG>
static Chromosome *crossover_child(const Chromosome *a, const Chromosome *b, RNG &rng) {
	auto result = a->clone();

	auto& result_ordering = result->get_ordering();

	// Fill in all of the remaining values
	for (size_t i = 1; i < result->get_ordering().size(); i++) {
		// Find all the neighbors of the LAST value
		auto neighbors = find_neighbors(a, b, a->get_ordering()[i-1]);
		// Remove any values from neighbors that are already in the resut order (so we don't get duplicates)
		auto new_end = std::remove_if(neighbors.begin(), neighbors.end(), [&](auto x) {
			return std::find(result_ordering.begin(), result_ordering.end(), x) != result_ordering.end();
		});
		// Erase actually removes the elements
		neighbors.erase(new_end, neighbors.end());

		auto min_neighbors = lowest_neighbors(a, b, neighbors);
		auto index = rng() % min_neighbors.size();
		result_ordering[i] = min_neighbors[index];

	}

	assert(result->is_valid());

	return result;
}

std::pair<Chromosome *, Chromosome *> CrossoverChromosome::recombine(const Chromosome* other) {
	auto a = crossover_child(this, other, generator_);
	auto b = crossover_child(other, this, generator_);

	return {a, b};
}








