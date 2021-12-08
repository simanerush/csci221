#pragma once

#include "climb_chromosome.hh"
#include "deme.hh"

class TournamentDeme : public Deme {
public:
	TournamentDeme(const Cities* cities_ptr, unsigned pop_size, double mut_rate) 
	: Deme(cities_ptr, pop_size, mut_rate) {
		for (auto &x : pop_) {
			// Deme class had already created Chromosomes, so we need to delete it.
			delete x;
			x = new ClimbChromosome(cities_ptr);
		}
	}

	virtual Chromosome *select_parent() override;
};