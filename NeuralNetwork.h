#pragma once
#include <vector>
#include "DenseLayer.h"

template<int INPUTS, int OUTPUTS, int NEURONS_PER_HIDDEN>
class NeuralNetwork
{
public:
	NeuralNetwork(unsigned int numOfHiddenLayers = 1)
		:m_pSingleHiddenLayer{nullptr}
		,m_pFirstHiddenLayer{nullptr}
		,m_pLastHiddenLayer{nullptr}
		,m_pOtherHiddenLayers{}
	{
		// Setting the right shapes for the layers
		switch (numOfHiddenLayers)
		{
		case 1:
			m_pSingleHiddenLayer = new DenseLayer<INPUTS, OUTPUTS>{};
			break;
		default:
			for (size_t i{ 0 }; i < numOfHiddenLayers; ++i)
			{
				m_pOtherHiddenLayers.push_back(new DenseLayer<NEURONS_PER_HIDDEN, NEURONS_PER_HIDDEN>{});
			}
		case 2:
			m_pFirstHiddenLayer = new DenseLayer<INPUTS, NEURONS_PER_HIDDEN>{};
			m_pLastHiddenLayer = new DenseLayer<NEURONS_PER_HIDDEN, OUTPUTS>{};
			break;
		}
	}

	~NeuralNetwork()
	{
		delete m_pFirstHiddenLayer;
		m_pFirstHiddenLayer = nullptr;

		delete m_pLastHiddenLayer;
		m_pLastHiddenLayer = nullptr;

		delete m_pSingleHiddenLayer;
		m_pSingleHiddenLayer = nullptr;

		for (int i{0}; i < m_pOtherHiddenLayers.size(); ++i)
		{
			delete m_pOtherHiddenLayers[i];
			m_pOtherHiddenLayers[i] = nullptr;
		}
	}

	NeuralNetwork(const NeuralNetwork& other) = delete;
	NeuralNetwork(NeuralNetwork&& other) = delete;
	NeuralNetwork& operator=(const NeuralNetwork& other) = delete;
	NeuralNetwork& operator=(NeuralNetwork&& other) = delete;

	// Goes thrue all the initialized layers and forwards to the last one to get the output
	void Forward(const std::array<float, INPUTS>& inputs)
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

	std::array<float, OUTPUTS> Output() const
	{
		return m_Output;
	}
private:
	DenseLayer<INPUTS, NEURONS_PER_HIDDEN>* m_pFirstHiddenLayer;
	DenseLayer<NEURONS_PER_HIDDEN, OUTPUTS>* m_pLastHiddenLayer;

	// Only used when there is just 1 hidden layer
	DenseLayer<INPUTS, OUTPUTS>* m_pSingleHiddenLayer;

	//Only used when there are 3 or more hidden layers
	std::vector<DenseLayer<NEURONS_PER_HIDDEN, NEURONS_PER_HIDDEN>*> m_pOtherHiddenLayers;
	
	std::array<float, OUTPUTS> m_Output{};
};

