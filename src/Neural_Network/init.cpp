#include <string>

#include "NeuralNet.h"
#include "../utilities/util.h"


NN::NN(const std::vector<unsigned int>& _dimensions)
	:	m_id(++count), m_total_value_count(0), m_layer_count(_dimensions.size() - 1), 
		m_dimensions(m_layer_count), m_input_count(_dimensions[0]),

		m_input(nullptr),
		// value*, value*, value*, bias*, bias*, bias*, grad*, grad* (...)
		m_neuron_value(new float*[m_layer_count * PARAMETER_COUNT_NEURON]),
		m_neuron_bias(m_neuron_value + m_layer_count), 
		m_neuron_gradient(m_neuron_bias + m_layer_count),
		m_neuron_step(m_neuron_gradient + m_layer_count),
														
		m_weight(new float*[(m_layer_count) * PARAMETER_COUNT_WEIGHT]),
		m_weight_step(m_weight + m_layer_count)
{
	ASSERT(m_layer_count > 0 && m_layer_count < 1000);

	for (int i = 0; i < m_layer_count; i++) // initialization of m_dimentions vector
	{
		m_dimensions[i] = _dimensions[i + 1];
	}

	// Allocate memory
	{
		m_total_value_count = m_input_count;
		for (unsigned int i = 0; i < m_layer_count; i++) //neurons memory requirement
		{
			m_total_value_count += m_dimensions[i] * PARAMETER_COUNT_NEURON;
		}

		m_total_value_count += m_input_count * m_dimensions[0] * PARAMETER_COUNT_WEIGHT;
		for (unsigned int i = 1; i < m_layer_count; i++) //weights memory requirement
		{
			m_total_value_count += m_dimensions[i - 1] * m_dimensions[i] * PARAMETER_COUNT_WEIGHT;
		}

		if (m_total_value_count * sizeof(float) + total_memory > MEMORY_CAP) [[unlikely]]
		{
			logger::consoleLog("Exeeded max. memory capacity of " + std::to_string(MEMORY_CAP) + " bytes", ERROR);  
			ASSERT(false);
		}

		m_input = static_cast<float*>(_aligned_malloc(m_total_value_count * sizeof(float), MEMORY_ALIGNEMENT)); // SIMD aligned allocation of calculated size
		
		if (!m_input) [[unlikely]]
		{
			logger::consoleLog("Memory allocation bad", ERROR); 
			ASSERT(false); 
		}

		m_weight[0] = m_input + m_input_count;
		memset(m_input, 0, m_total_value_count * sizeof(float));


		total_memory += m_total_value_count * sizeof(float);
	}

	// Get layer addresses
	{
		for (unsigned int offset_in_allocation = 0, i = 0; i < m_layer_count; i++)
		{
			if(i == 0)
			{
				m_weight_step[0] = m_weight[0] + m_input_count * m_dimensions[0];
				offset_in_allocation += m_input_count * m_dimensions[0] * PARAMETER_COUNT_WEIGHT;
			}
			else
			{
				m_weight[i] = m_weight[0] + offset_in_allocation;
				m_weight_step[i] = m_weight[i] + m_dimensions[i - 1] * m_dimensions[i];

				offset_in_allocation += m_dimensions[i - 1] * m_dimensions[i] * PARAMETER_COUNT_WEIGHT;
			}
			
			m_neuron_value[i] = m_weight[0] + offset_in_allocation;
			m_neuron_bias[i] = m_neuron_value[i] + m_dimensions[i];
			m_neuron_gradient[i] = m_neuron_bias[i] + m_dimensions[i];
			m_neuron_step[i] = m_neuron_gradient[i] + m_dimensions[i];

			offset_in_allocation += m_dimensions[i] * PARAMETER_COUNT_NEURON;
		}
	}

	// Randomize weights and biases
	{
		for (unsigned int i_weight = 0; i_weight < m_input_count * m_dimensions[0]; i_weight++)
		{
			m_weight[0][i_weight] = math::random(WEIGHT_INIT_RANGE);
			m_weight_step[0][i_weight] = 0;
		}

		for (unsigned int i_layer = 1; i_layer < m_layer_count; i_layer++) //weights
		{
			for (unsigned int total_weights = m_dimensions[i_layer - 1] * m_dimensions[i_layer], i_weight = 0; i_weight < total_weights; i_weight++)
			{
				m_weight[i_layer][i_weight] = math::random(WEIGHT_INIT_RANGE);
				m_weight_step[i_layer][i_weight] = 0;
			}
		}
		
		for (unsigned int i_layer = 0; i_layer < m_layer_count; i_layer++) //biases
		{
			for (int i_neuron = 0; i_neuron < m_dimensions[i_layer]; i_neuron++)
			{
				m_neuron_value[i_layer][i_neuron] = 0;
				m_neuron_bias[i_layer][i_neuron] = math::random(BIAS_INIT_RANGE);
				m_neuron_gradient[i_layer][i_neuron] = 0;
				m_neuron_step[i_layer][i_neuron] = 0;
			}
		}
		
	}

	logger::consoleLog("Initialized network " + std::to_string(m_id), INFO);
	logger::consoleLog("Allocated " + std::to_string(m_total_value_count) + " * " + std::to_string(sizeof(float)) + " bytes of memory.", SUB_INFO);
	logger::consoleLog("Total initialized memory: " + std::to_string(total_memory) + " bytes", SUB_INFO);
	
	m_input[0] = 1;
	m_input[1] = 1;
	fwrdProp();
	backProp();
}

NN::~NN() 
{
	_aligned_free(m_input);

	delete[] m_neuron_value;
	delete[] m_weight;

	logger::consoleLog("Released network " + std::to_string(m_id), INFO);
}
