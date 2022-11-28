#include "pch.h"
#include "Population.h"
#include "Individual.h"

Population::Population(int populationSize)
{
	m_pIndividuals.reserve(populationSize);
}

void Population::Initialize()
{
	for (size_t i{ 0 }; i < Size(); ++i)
	{
		Individual* pIndividual = new Individual{};
		pIndividual->Generate();
		SaveIndividual(i, pIndividual);
	}
}

Individual* Population::GetIndividual(size_t index) const
{
	return m_pIndividuals.at(index);
}

Individual* Population::GetFittestIndividual() const
{
	Individual* pFittestIndividual = m_pIndividuals.at(0);

	for (size_t i{ 0 }; i < Size(); ++i)
	{
		if (pFittestIndividual->GetFitness() <= GetIndividual(i)->GetFitness())
		{
			pFittestIndividual = GetIndividual(i);
		}
	}
	return pFittestIndividual;
}

size_t Population::Size() const
{
	return m_pIndividuals.size();
}

void Population::SaveIndividual(size_t index, Individual* pIndividual)
{
	m_pIndividuals.at(index) = pIndividual;
}
