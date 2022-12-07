#pragma once
#include <vector>

class Individual;

class Population
{
public:
	Population(int populationSize, const Rectf& mapBounds);
	~Population();

	Population(const Population& other) = delete;
	Population(Population&& other) = delete;
	Population& operator=(const Population& other) = delete;
	Population& operator=(Population&& other) = delete;

	void Update(float deltaTime);
	void Draw() const;

	Individual* GetIndividual(size_t index) const;
	Individual* GetFittestIndividual() const;
	size_t Size() const;
private:
	void Initialize();

	std::vector<Individual*> m_pIndividuals;
	int indexOfCurrentEvaluatedIndividual{ 0 };
	Rectf m_MapBounds;
};

