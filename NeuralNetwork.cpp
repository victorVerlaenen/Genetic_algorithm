#include "pch.h"
#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork(unsigned int numberOfInputs, unsigned int numberOfOutputs, unsigned int numberOfNeuronsPerHiddenLayer, unsigned int numOfHiddenLayers)
	:m_pSingleHiddenLayer{ nullptr }
	, m_pFirstHiddenLayer{ nullptr }
	, m_pLastHiddenLayer{ nullptr }
	, m_pOtherHiddenLayers{}
	, m_NumberOfInputs{ numberOfInputs }
	, m_NumberOfOutputs{ numberOfOutputs }
	, m_NumberOfNeuronsPerHiddenLayer{ numberOfNeuronsPerHiddenLayer }
{
	// Setting the right shapes for the layers
	switch (numOfHiddenLayers)
	{
	case 1:
		m_pSingleHiddenLayer = new DenseLayer{ numberOfInputs, numberOfOutputs };
		break;
	default:
		for (size_t i{ 0 }; i < numOfHiddenLayers; ++i)
		{
			m_pOtherHiddenLayers.push_back(new DenseLayer{ numberOfNeuronsPerHiddenLayer, numberOfNeuronsPerHiddenLayer });
		}
	case 2:
		m_pFirstHiddenLayer = new DenseLayer{ numberOfInputs, numberOfNeuronsPerHiddenLayer };
		m_pLastHiddenLayer = new DenseLayer{ numberOfNeuronsPerHiddenLayer, numberOfOutputs };
		break;
	}
}

NeuralNetwork::~NeuralNetwork()
{
	delete m_pFirstHiddenLayer;
	m_pFirstHiddenLayer = nullptr;

	delete m_pLastHiddenLayer;
	m_pLastHiddenLayer = nullptr;

	delete m_pSingleHiddenLayer;
	m_pSingleHiddenLayer = nullptr;

	for (int i{ 0 }; i < m_pOtherHiddenLayers.size(); ++i)
	{
		delete m_pOtherHiddenLayers[i];
		m_pOtherHiddenLayers[i] = nullptr;
	}
}

// Goes thrue all the initialized layers and forwards to the last one to get the output
void NeuralNetwork::Forward(const std::vector<float>& inputs)
{
	if (m_pSingleHiddenLayer != nullptr)
	{
		m_pSingleHiddenLayer->Forward(inputs);
		m_Output = m_pSingleHiddenLayer->Output();
		return;
	}

	m_pFirstHiddenLayer->Forward(inputs);
	auto nextInputForLayer = m_pFirstHiddenLayer->Output();
	for (auto& pLayer : m_pOtherHiddenLayers)
	{
		pLayer->Forward(nextInputForLayer);
		nextInputForLayer = pLayer->Output();
	}
	m_pLastHiddenLayer->Forward(nextInputForLayer);
	m_Output = m_pLastHiddenLayer->Output();

}

std::vector<float> NeuralNetwork::Output() const
{
	return m_Output;
}