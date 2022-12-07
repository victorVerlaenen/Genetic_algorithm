#pragma once
#include "Defines.h"
#include <algorithm>
#include <random>
#include <iostream>
#include <array>

class DenseLayer
{
public:
	DenseLayer(unsigned int numberOfInputs, unsigned int numberOfNeurons);
	~DenseLayer() = default;

	DenseLayer(const DenseLayer& other) = delete;
	DenseLayer(DenseLayer&& other) = delete;
	DenseLayer& operator=(const DenseLayer& other) = delete;
	DenseLayer& operator=(DenseLayer&& other) = delete;

	void Forward(const std::vector<float>& inputs);
	std::vector<float> Output() const;
	void PrintOutput() const;

private:
	void ActivationReLu();

	Matrix2D<float> m_Weights{};
	std::vector<float> m_Output{};
	std::vector<float> m_Biases{};

	unsigned int m_NumberOfInputs;
	unsigned int m_NumberOfNeurons;
};