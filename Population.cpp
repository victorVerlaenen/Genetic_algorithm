#include "pch.h"
#include "Population.h"
#include "Individual.h"
#include "Food.h"
#include <iostream>

Population::Population(int populationSize, const Rectf& mapBounds, Food* pFood)
	:m_MapBounds{ mapBounds }
	, m_pFood{ pFood }
{
	m_pIndividuals.resize(populationSize);
	Individual::SetFood(m_pFood);
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
		m_pIndividuals[i]->SetFood(m_pFood);
	}
	std::cout << "Current individual: " << indexOfCurrentEvaluatedIndividual << std::endl;
}

void Population::SetNewIndividuals(const std::vector<Individual*>& newIndividuals)
{
	for (int i{ 0 }; i < Size(); ++i)
	{
		delete m_pIndividuals[i];
		m_pIndividuals[i] = newIndividuals[i];
	}

	// Reset needed values
	m_CurrentTime = 0;
	m_pFood->Reset();
	indexOfCurrentEvaluatedIndividual = 0;
}

void Population::Update(float deltaTime)
{
	// Update the timer
	m_CurrentTime += deltaTime;

	// Go to next individual when current has died
	if (m_pIndividuals[indexOfCurrentEvaluatedIndividual]->IsDead() == true)
	{
		m_pIndividuals[indexOfCurrentEvaluatedIndividual]->Reset();

		// Reset food when individual restarts
		m_pFood->Reset();
	}

	if (m_CurrentTime >= m_TimePerIndividual
		&& indexOfCurrentEvaluatedIndividual < m_pIndividuals.size() - 1)
	{
		m_pIndividuals[indexOfCurrentEvaluatedIndividual]->CalculateFitness();

		indexOfCurrentEvaluatedIndividual++;
		std::cout << "Current individual: " << indexOfCurrentEvaluatedIndividual << std::endl;

		// Reset food when individual starts
		m_pFood->Reset();

		// Reset the timer
		m_CurrentTime = 0;
	}

	// Update current individual
	m_pIndividuals[indexOfCurrentEvaluatedIndividual]->Update(deltaTime);
}

bool Population::IsDone() const
{
	if (indexOfCurrentEvaluatedIndividual >= m_pIndividuals.size())
	{
		return true;
	}
	return false;
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