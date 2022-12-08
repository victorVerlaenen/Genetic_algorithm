#pragma once

class Population;
class Individual;
class GeneticAlgorithm
{
public:
	GeneticAlgorithm(int numberOfGenerations);
	~GeneticAlgorithm() = default;

	GeneticAlgorithm(const GeneticAlgorithm& other) = delete;
	GeneticAlgorithm(GeneticAlgorithm&& other) = delete;
	GeneticAlgorithm& operator=(const GeneticAlgorithm& other) = delete;
	GeneticAlgorithm& operator=(GeneticAlgorithm&& other) = delete;

	void Update(float deltaTime);
	void Draw() const;

	void EvolvePopulation();
private:
	Individual* TournamentSelection(int tournamentSize) const;
	std::array<Individual*, 2> OnePointCrossover(Individual* pParent01, Individual* pParent02);

	int m_Generation{ 0 };
	int m_AmountOfGenerations;
	Population* m_pPopulation;
};