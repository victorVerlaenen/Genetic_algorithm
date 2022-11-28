#pragma once
#include <vector>

class Individual
{
public:
	Individual();
	~Individual() = default;

	Individual(const Individual& other) = delete;
	Individual(Individual&& other) = delete;
	Individual& operator=(const Individual& other) = delete;
	Individual& operator=(Individual&& other) = delete;

	void Generate();


	static void SetDefaultGeneLength(int length);
	static int m_DefaultGeneLength;

	int GetFitness() const;
private:
	std::vector<unsigned char> m_Genes{};
	int m_Fitness{ 0 };

};

