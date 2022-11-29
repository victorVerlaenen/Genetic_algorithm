#include "pch.h"
#include "Layer.h"
#include <numeric>

Layer::Layer(int numOfInputs, int numOfNeurons)
{
	// Set the amount of biases equal to the amount of neurons in the layer
	// and for now seet them equal to 0
	for (int j{ 0 }; j < numOfNeurons; ++j)
	{
		m_Biases.push_back(0);
	}

	// 
	for (int i{ 0 }; i < numOfInputs; ++i)
	{
		m_Weights.data.push_back({});
		for (int j{ 0 }; j < numOfNeurons; ++j)
		{
			m_Weights.data[i].push_back((rand() % 201 - 100) / 100.0f * 0.1f);
		}
	}
}

void Layer::Forward(const Matrixf& inputs)
{
	// Inputs * Weights + Biases
	Matrixf transposedMatrix = m_Weights.Transpose();
	Matrixf multiplicationResult;
	for (size_t i = 0; i < inputs.data.size(); i++) {
		multiplicationResult.data.push_back({});
		for (size_t j = 0; j < transposedMatrix.data.size(); j++) {
			multiplicationResult.data[i].push_back(std::inner_product(inputs.data[i].begin(), inputs.data[i].end(), transposedMatrix.data[j].begin(), 0.0f));
		}
	}

	for (size_t j = 0; j < multiplicationResult.data.size(); j++) {
		m_Outputs.data.push_back({});
		for (size_t i = 0; i < multiplicationResult.data[0].size(); i++) {
			m_Outputs.data[j].push_back(multiplicationResult.data[j][i] + m_Biases[i]);
		}
	}
}

Matrixf Layer::Output() const
{
	return m_Outputs;
}
