#pragma once
#include "chromosome.hh"

class ClimbChromosome : public Chromosome {
public:
	ClimbChromosome(const Cities *cities_ptr) : Chromosome(cities_ptr) {}

	virtual void mutate() override;
	virtual Chromosome* clone() const override {return new ClimbChromosome(cities_ptr_); }
};