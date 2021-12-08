#include "climb_chromosome.hh"

void ClimbChromosome::mutate() {
	// p is a random point. get two points from order and swap them
	std::uniform_int_distribution<size_t> random{0, order_.size() - 1};
	auto fitness = get_fitness();
	auto index = random(generator_);
	auto new_order = order_;
	if (index == 0) {
		std::swap(new_order.front(), new_order.back());
	} else {
		std::swap(new_order[index], new_order[index - 1]);
	}

	std::swap(new_order, order_);
	auto new_fitness = get_fitness();
	std::swap(new_order, order_);

	auto newer_order = order_;
	std::swap(newer_order[index], newer_order[(index + 1) % newer_order.size()]);

	std::swap(newer_order, new_order);
	auto newer_fitness = get_fitness();
	std::swap(newer_order, new_order);

	if (fitness > new_fitness) {
		if (fitness > newer_fitness) {
			// Do nothing: means that order is already associated with the highest fitness
		} else {
			std::swap(newer_order, order_);
		}
	} else {
		if (new_fitness > newer_fitness) {
			std::swap(new_order, order_);
		} else {
			std::swap(newer_order, order_);
		}
	}
}

Chromosome* clone()  {

}
