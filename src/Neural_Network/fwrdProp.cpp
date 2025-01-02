#include "NeuralNet.h"

void NN::fwrdProp() 
{
	for (unsigned int i_neuron = 0; i_neuron < m_dimensions[0]; i_neuron++)
	{
		float neuron_value = 0;

		for (unsigned int i_input = 0; i_input < m_input_count; i_input++)
		{
			neuron_value += m_input[i_input] * m_weight[0][i_neuron * m_input_count + i_input];
		}
		m_neuron_value[0][i_neuron] = math::ReLU(neuron_value);
	}

	for (unsigned int prev_layer = 0, layer = 1; layer < m_layer_count; layer++) 
	{
		for (unsigned int i_neuron = 0; i_neuron < m_dimensions[layer]; i_neuron++)
		{
			float neuron_value = 0;

			for (unsigned int i_prev_neuron = 0; i_prev_neuron < m_dimensions[prev_layer]; i_prev_neuron++)
			{
				neuron_value += (m_neuron_value[prev_layer][i_prev_neuron] + m_neuron_bias[prev_layer][i_prev_neuron]) * m_weight[layer][i_neuron * m_dimensions[prev_layer] + i_prev_neuron];
			}

			m_neuron_value[layer][i_neuron] = math::ReLU(neuron_value);
		}
		prev_layer++;
	}
}