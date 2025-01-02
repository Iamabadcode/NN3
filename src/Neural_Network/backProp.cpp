#include "NeuralNet.h"

float cost_derrivative(float x) { return x; }

void NN::backProp() 
{
	// layer one:
	//	
	//	grad = weight * 
	// 
	// cost =  cost(val * weight + bias) 
	// 
	// -> gradient = cost'(val) * weight
	const unsigned int last_layer_index = m_layer_count - 1;
	for (unsigned int i_neuron = 0; i_neuron < m_dimensions[last_layer_index]; i_neuron++)
	{
		m_neuron_gradient[last_layer_index][i_neuron] = cost_derrivative(m_neuron_value[last_layer_index][i_neuron]) * m_weight[last_layer_index][1];
	}

	
	//
	//
	//
	//
	//
}