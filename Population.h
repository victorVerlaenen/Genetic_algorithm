#pragma once
#include <vector>

class Individual;
class Food;
class Population
{
public:
	Population(int populationSize, const Rectf& mapBounds, Food* pFood);
	~Population();

	Population(const Population& other) = delete;
	Population(Population&& other) = delete;
	Population& operator=(const Population& other) = delete;
	Population& operator=(Population&& other) = delete;

	void Initialize();
	void Update(float deltaTime);
	void Draw() const;

	Individual* GetIndividual(size_t index) const;
	Individual* GetFittestIndividual() const;
	void SetNewIndividuals(const std::vector<Individual*>& newIndividuals);
	size_t Size() const;

	bool IsDone() const;
private:

	std::vector<Individual*> m_pIndividuals;
	int indexOfCurrentEvaluatedIndividual{ 0 };
	Rectf m_MapBounds;

	float m_TimePerIndividual{ 20 };
	float m_CurrentTime{ 0 };

	Food* m_pFood;
};

