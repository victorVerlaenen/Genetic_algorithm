#include "pch.h"
#include "Individual.h"

int Individual::m_DefaultGeneLength = 64;

Individual::Individual()
{
	m_Genes.reserve(m_DefaultGeneLength);
}

void Individual::Generate()
{
	
}

int Individual::GetFitness() const
{
	// TODO calculate fitness
	return 0;
}
