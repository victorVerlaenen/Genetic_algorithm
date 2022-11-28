#pragma once

class Layer
{
public:
	Layer(int numOfInputs, int numOfNeurons);

	void Forward(const Matrixf& inputs);
	Matrixf Output() const;
private:

	Matrixf m_Weights, m_Outputs;
	std::vector<float> m_Biases;
};

