#include "NeuralNet.h"

float cost_derrivative(float x) { return x; }

void NN::backProp() 
{
	const unsigned int last_layer_index = m_layer_count - 1;
	for (unsigned int i_neuron = 0; i_neuron < m_dimensions[last_layer_index]; i_neuron++)
	{
		m_neuron_gradient[last_layer_index][i_neuron] = cost_derrivative(math::ReLU_d(m_neuron_value[last_layer_index][i_neuron]));
	}

	for (unsigned int i_prev_layer = last_layer_index, i_layer = last_layer_index; i_layer > 0; i_prev_layer--)
	{
		i_layer--;
		unsigned int layer_neuron_count = m_dimensions[i_layer];

		for (unsigned int i_neuron = 0; i_neuron < layer_neuron_count; i_neuron++)
		{
			float neuron_gradient = 0;
			for (unsigned int i_prev_layer_neuron = 0; i_prev_layer_neuron < m_dimensions[i_prev_layer]; i_prev_layer_neuron++)
			{
				neuron_gradient += m_neuron_gradient[i_prev_layer][i_prev_layer_neuron] * m_weight[i_prev_layer][i_prev_layer_neuron * layer_neuron_count + i_neuron];
			}
			m_neuron_gradient[i_layer][i_neuron] = neuron_gradient * math::ReLU_d(m_neuron_value[i_layer][i_neuron]);
		}
	}
}