#pragma once
#include <xtensor.hpp>

class Layer
{
public:
	Layer(int numOfInputs, int numOfNeurons);

	void Forward(const xt::xarray<float>& inputs);
	xt::xarray<float> Output() const;
private:

	xt::xarray<float> m_Weights, m_Output;
	xt::xarray<float> m_Biases;
};

