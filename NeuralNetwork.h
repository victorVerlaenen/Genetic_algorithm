#pragma once
#include <vector>

class Layer;

class NeuralNetwork
{
public:
	NeuralNetwork();
	~NeuralNetwork() = default;

	NeuralNetwork(const NeuralNetwork& other) = delete;
	NeuralNetwork(NeuralNetwork&& other) = delete;
	NeuralNetwork& operator=(const NeuralNetwork& other) = delete;
	NeuralNetwork& operator=(NeuralNetwork&& other) = delete;

private:
	int m_InputAmount{ 0 };
	int m_OutputAmount{ 0 };
	std::vector<float> m_Inputs{};
	std::vector<float> m_Outputs{};

	Layer* m_pInputLayer{};
	std::vector<Layer*> m_pHiddenLayers{};
	Layer* m_pOutputLayer{};
};

