#pragma once

#include "climb_chromosome.hh"

class CrossoverChromosome: public ClimbChromosome {
public:
	CrossoverChromosome(const Cities *cities_ptr) : ClimbChromosome(cities_ptr) {}
	virtual std::pair<Chromosome *, Chromosome *> recombine(const Chromosome* other) override;

private:
	static Chromosome *create_crossover_child(const Chromosome *a, const Chromosome *b);
};

