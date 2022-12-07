#include "pch.h"
#include "Population.h"
#include "Individual.h"

Population::Population(int populationSize, const Rectf& mapBounds)
	:m_MapBounds{ mapBounds }
{
	m_pIndividuals.resize(populationSize);
	Initialize();
}

Population::~Population()
{
	for (int i{ 0 }; i < Size(); ++i)
	{
		delete m_pIndividuals[i];
		m_pIndividuals[i] = nullptr;
	}
}

void Population::Initialize()
{
	for (int i{ 0 }; i < m_pIndividuals.size(); ++i)
	{
		m_pIndividuals[i] = new Individual{ Point2f{m_MapBounds.width / 2, m_MapBounds.height / 2}, m_MapBounds };
	}
	std::cout << "Current individual: " << indexOfCurrentEvaluatedIndividual << std::endl;
}

void Population::Update(float deltaTime)
{
	if (m_pIndividuals[indexOfCurrentEvaluatedIndividual]->IsDead() == true
		&& indexOfCurrentEvaluatedIndividual < m_pIndividuals.size() - 1)
	{
		indexOfCurrentEvaluatedIndividual++;
		std::cout << "Current individual: " << indexOfCurrentEvaluatedIndividual << std::endl;
	}
	m_pIndividuals[indexOfCurrentEvaluatedIndividual]->Update(deltaTime);
}

void Population::Draw() const
{
	m_pIndividuals[indexOfCurrentEvaluatedIndividual]->Draw();
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
