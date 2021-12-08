/*
 * Declarations for Deme class to evolve a genetic algorithm for the
 * travelling-salesperson problem.  A deme is a population of individuals.
 */

#include "chromosome.hh"
#include "crossover.hh"
#include "deme.hh"

// Generate a Deme of the specified size with all-random chromosomes.
// Also receives a mutation rate in the range [0-1].
Deme::Deme(const Cities* cities_ptr, unsigned pop_size, double mut_rate) 
: pop_(pop_size), mut_rate_(mut_rate), generator_(rand())
{
  for (auto& x : pop_) {
    x = new CrossoverChromosome(cities_ptr);
  }
}

// Clean up as necessary
Deme::~Deme()
{
  for (auto& x : pop_) {
    delete x;
  }
}

// Evolve a single generation of new chromosomes, as follows:
// We select pop_size/2 pairs of chromosomes (using the select() method below).
// Each chromosome in the pair can be randomly selected for mutation, with
// probability mut_rate, in which case it calls the chromosome mutate() method.
// Then, the pair is recombined once (using the recombine() method) to generate
// a new pair of chromosomes, which are stored in the Deme.
// After we've generated pop_size new chromosomes, we delete all the old ones.
void Deme::compute_next_generation()
{
  std::bernoulli_distribution rand(mut_rate_);

  std::vector<Chromosome *> all_children{};
  // Allocate the block to get rid of constantly allocationg new memory
  all_children.reserve(pop_.size());

  // Compute the fitnesses for every generation
  fitnesses_.reserve(pop_.size());
  for (const auto& x : pop_) {
    auto fitness = x->get_fitness();
    fitnesses_.push_back(fitness);
  }

  for (size_t i = 0; i < pop_.size() / 2; i++) {
    auto chromo_a = select_parent();
    auto chromo_b = select_parent();

    auto rand_a = rand(generator_);
    auto rand_b = rand(generator_);

    if (rand_a) {
      chromo_a->mutate();
    }

    if (rand_b) {
      chromo_b->mutate();
    }

    auto children = chromo_a->recombine(chromo_b);

    all_children.push_back(children.first);
    all_children.push_back(children.second);
  }

  fitnesses_.clear();
  pop_.swap(all_children);
  for (auto& x : all_children) {
    delete x;
  }
}

// Return a copy of the chromosome with the highest fitness.
const Chromosome* Deme::get_best() const
{
  double best_fitness = std::numeric_limits<double>::min();
  Chromosome *best = nullptr;
  for (const auto& x : pop_) {
    auto x_fitness = x->get_fitness();
    if (!best || best_fitness < x_fitness) {
      best = x;
      best_fitness = x_fitness;
    }
  }
  return best;
}

bool compare_fitness(const Chromosome *a, const Chromosome *b) {
  return a->get_fitness() < b -> get_fitness();
}

double add_fitness(const double& sum, const Chromosome* chromo) {
  return sum + chromo->get_fitness();
}

// Randomly select a chromosome in the population based on fitness and
// return a pointer to that chromosome.
Chromosome* Deme::select_parent()
{
  // Sums up all fitnesses
  auto total_fitness = std::accumulate(fitnesses_.begin(), fitnesses_.end(), 0.0);

  std::uniform_real_distribution<> rand(0.0, total_fitness);
  auto random = rand(generator_);
  auto sum = 0.0;
  for (size_t i = 0; i < pop_.size(); i++) {
    sum += fitnesses_[i];
    if (sum > random) {
      return pop_[i];
    }
  }

  // Since the sum should equal total fitness by the end, and random is less than total fitness, 
  // that should never happen.
  return nullptr;

}
