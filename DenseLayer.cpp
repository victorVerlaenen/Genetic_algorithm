#include "pch.h"
#include "DenseLayer.h"

DenseLayer::DenseLayer(unsigned int numberOfInputs, unsigned int numberOfNeurons)
	:m_NumberOfInputs{ numberOfInputs }
	, m_NumberOfNeurons{ numberOfNeurons }
{
	// Random
	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_real_distribution<float> distr(-1, 1);

	// Fill the weights matrix with random values between -1 and 1
	for (size_t i{ 0 }; i < numberOfNeurons; ++i)
	{
		m_Weights.push_back({});
		for (size_t j{ 0 }; j < numberOfInputs; ++j)
		{
			m_Weights[i].push_back({});
			m_Weights[i][j] = 0.1f * distr(eng);
		}
	}

	// Fill biases with 0
	for (size_t i{ 0 }; i < numberOfNeurons; ++i)
	{
		m_Biases.push_back(0);
	}
}

void DenseLayer::Forward(const std::vector<float>& inputs)
{
	// For every neuron
	for (size_t i{ 0 }; i < m_NumberOfNeurons; ++i)
	{
		m_Output.push_back(0);
		// For every weight
		for (size_t j{ 0 }; j < m_NumberOfInputs; ++j)
		{
			m_Output[i] += inputs[j] * m_Weights[i][j];
		}
		m_Output[i] += m_Biases[i];
	}

	// Rectified linear activation function
	ActivationReLu();
}

std::vector<float> DenseLayer::Output() const
{
	return m_Output;
}

void DenseLayer::PrintOutput() const
{
	for (auto value : m_Output)
	{
		std::cout << value << ", ";
	}
}

void DenseLayer::ActivationReLu()
{
	for (float& outputValue : m_Output)
	{
		outputValue = std::max(0.0f, outputValue);
	}
}