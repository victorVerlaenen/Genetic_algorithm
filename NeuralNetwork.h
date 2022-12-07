#pragma once
#include <vector>
#include "DenseLayer.h"

class NeuralNetwork
{
public:
	NeuralNetwork(unsigned int numberOfInputs, unsigned int numberOfOutputs, unsigned int numberOfNeuronsPerHiddenLayer, unsigned int numOfHiddenLayers = 1);
	~NeuralNetwork();

	NeuralNetwork(const NeuralNetwork& other) = delete;
	NeuralNetwork(NeuralNetwork&& other) = delete;
	NeuralNetwork& operator=(const NeuralNetwork& other) = delete;
	NeuralNetwork& operator=(NeuralNetwork&& other) = delete;

	// Goes thrue all the initialized layers and forwards to the last one to get the output
	void Forward(const std::vector<float>& inputs);
	std::vector<float> Output() const;

private:
	DenseLayer* m_pFirstHiddenLayer;
	DenseLayer* m_pLastHiddenLayer;

	// Only used when there is just 1 hidden layer
	DenseLayer* m_pSingleHiddenLayer;

	//Only used when there are 3 or more hidden layers
	std::vector<DenseLayer*> m_pOtherHiddenLayers;

	std::vector<float> m_Output{};

	unsigned int m_NumberOfInputs;
	unsigned int m_NumberOfOutputs;
	unsigned int m_NumberOfNeuronsPerHiddenLayer;
};

