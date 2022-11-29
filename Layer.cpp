#include "pch.h"
#include "Layer.h"
#include <numeric>

Layer::Layer(int numOfInputs, int numOfNeurons)
{
	// Makes a matrix of shape [numOfNeurons x numOfInputs] and fills it with random values
	m_Weights = 0.01 * xt::random::randn<float>({ numOfNeurons, numOfInputs });

	// Makes a matrix of shape [1 x numOfNeurons] and fills it with 0's
	m_Biases = xt::zeros<float>({ 1, numOfNeurons });
}

void Layer::Forward(const xt::xarray<float>& inputs)
{
	
}

xt::xarray<float> Layer::Output() const
{
	return m_Outputs;
}
