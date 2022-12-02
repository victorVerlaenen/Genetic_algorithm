#pragma once
#include <xtensor.hpp>
#include "Defines.h"

template<int INPUTS, int NEURONS>
class Layer
{
public:
	Layer()
	{
		// Random
		std::random_device rd;
		std::default_random_engine eng(rd());
		std::uniform_real_distribution<float> distr(-1, 1);

		// Fill the weights matrix with random values between -1 and 1
		for (auto& row : m_Weights)
		{
			for (auto& weight : row)
			{
				weight = 0.1f * distr(eng);
			}
		}

		// Fill biases with 0
		for (auto& bias : m_Biases)
		{
			bias = 0;
		}
	}

	void Forward(const std::array<float, INPUTS>& inputs)
	{
		// For every neuron
		for (int i{ 0 }; i < NEURONS; ++i)
		{
			// For every weight
			for (int j{ 0 }; j < INPUTS; ++j)
			{
				m_Output[i] += inputs[j] * m_Weights[i][j];
			}
			m_Output[i] += m_Biases[i];
		}
	}

	std::array<float, NEURONS> Output() const
	{
		return m_Output;
	}

	void PrintOutput() const
	{
		for (auto value : m_Output)
		{
			std::cout << value << ", ";
		}
	}
private:

	Matrix2D<NEURONS, INPUTS> m_Weights{};
	std::array<float, NEURONS> m_Output{};
	std::array<float, NEURONS> m_Biases{};
};