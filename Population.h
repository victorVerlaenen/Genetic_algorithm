#pragma once
#include <vector>

class Individual;

class Population
{
public:
	Population(int populationSize);
	~Population() = default;

	Population(const Population& other) = delete;
	Population(Population&& other) = delete;
	Population& operator=(const Population& other) = delete;
	Population& operator=(Population&& other) = delete;

	void Initialize();
	Individual* GetIndividual(size_t index) const;
	Individual* GetFittestIndividual() const;
	size_t Size() const;
	void SaveIndividual(size_t index, Individual* pIndividual);
private:
	std::vector<Individual*> m_pIndividuals;
};

