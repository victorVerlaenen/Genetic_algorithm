#include "pch.h"
#include "GeneticAlgorithm.h"
#include "Individual.h"
#include "Population.h"

GeneticAlgorithm::GeneticAlgorithm(int numberOfGenerations)
	:m_AmountOfGenerations{ numberOfGenerations }
{

}

void GeneticAlgorithm::EvolvePopulation()
{
	m_Generation++;

	std::vector<Individual*> newIndividuals;
	std::array<Individual*, 2> offsprings;

	for (int i{0}; i<m_pPopulation->Size(); ++i)
	{
		offsprings = OnePointCrossover(TournamentSelection(3), TournamentSelection(3));
		newIndividuals.push_back(offsprings[0]);
		newIndividuals.push_back(offsprings[1]);
	}

	m_pPopulation->SetNewIndividuals(newIndividuals);
}

Individual* GeneticAlgorithm::TournamentSelection(int tournamentSize) const
{
	return{};
}

std::array<Individual*, 2> GeneticAlgorithm::OnePointCrossover(Individual* pParent01, Individual* pParent02)
{
	return{};
}

void GeneticAlgorithm::Update(float deltaTime)
{
	m_pPopulation->Update(deltaTime);

	if (m_pPopulation->IsDone())
	{
		EvolvePopulation();
	}

	if (m_Generation >= m_AmountOfGenerations)
	{
		// TODO: Save the best individual

	}
}

void GeneticAlgorithm::Draw() const
{
	m_pPopulation->Draw();
}