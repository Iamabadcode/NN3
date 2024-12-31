#include "NN.h"
#include "../utilities/util.h"
#include <malloc.h>
#include <string>

int NN::count = 0;
int NN::total_memory = 0;


NN::NN(const std::vector<int>& _dimensions)
	: m_dimensions(_dimensions), m_id(count + 1), m_layer_count(m_dimensions.size()),

		m_neuron_value(new float*[m_layer_count * PARAMETER_COUNT_NEURON]), // all neuron pointer in one spot
		m_neuron_bias(m_neuron_value + m_layer_count),
		m_neuron_gradient(m_neuron_bias + m_layer_count), //	value*, value*, value*, bias*, bias*, bias*, grad*, grad* (...)
		m_neuron_step(m_neuron_gradient + m_layer_count),	//	initialization in this ways foes not affect usage
														
		m_weight(new float*[m_layer_count * PARAMETER_COUNT_WEIGHT]), // all weight block in one spot
		m_weight_step(m_weight + m_layer_count - 1) // -1 because weights only go between layers, therefor there is 1 less weight block
{
	count++;
	
	// 1. allocate memory based on "float" size & dimentions of network
	
	for (int i = 0; i < m_layer_count; i++) // sum of neurons memory requirement
	{
		m_memory_size += m_dimensions[i] * PARAMETER_COUNT_NEURON;
	}
	for (int i = 1; i < m_layer_count; i++) // sum of weights memory requirement
	{
		m_memory_size += m_dimensions[i - 1] * m_dimensions[i] * PARAMETER_COUNT_WEIGHT;
	}

	if (m_memory_size * sizeof(float) + total_memory > MEMORY_CAP) //__ ability to add a limit for how much heap memory can be used
	{
		logger::consoleLog("Exeeded max. memory capacity of " + std::to_string(MEMORY_CAP) + " bytes", ERROR);  ASSERT(false);
	}

	m_neuron_value[0] = static_cast<float*>(_aligned_malloc(m_memory_size * sizeof(float), MEMORY_ALIGNEMENT)); // SIMD aligned allocation of calculated size
	//memset(p_neuron_value[0], 0, memory_size * sizeof(float));
	
	if (!m_neuron_value[0]) { logger::consoleLog("Memory allocation bad", ERROR); ASSERT(false); } // check allocation
	
	total_memory += m_memory_size * sizeof(float); // if allocation success, add to static (cross instance) meemory count
	
	m_neuron_bias[0] = m_neuron_value[0] + m_dimensions[0]; // initiation of the first layers pointers
	m_neuron_gradient[0] = m_neuron_bias[0] + m_dimensions[0];
	m_neuron_step[0] = m_neuron_gradient[0] + m_dimensions[0];

	//			2. get addresses from memory for arraylike access
	int n = m_dimensions[0] * PARAMETER_COUNT_NEURON;
	for (int i = 1; i < m_layer_count; i++) 
	{
		n += m_dimensions[i - 1] * m_dimensions[i] * PARAMETER_COUNT_WEIGHT;

		m_neuron_value[i] = m_neuron_value[0] + n;
		m_neuron_bias[i] = m_neuron_value[i] + m_dimensions[i];
		m_neuron_gradient[i] = m_neuron_bias[i] + m_dimensions[i];
		m_neuron_step[i] = m_neuron_gradient[i] + m_dimensions[i];

		n += m_dimensions[i] * PARAMETER_COUNT_NEURON;
	}

	n = 0;
	for (int i = 0; i < m_layer_count - 1; i++) 
	{
		n += m_dimensions[i] * PARAMETER_COUNT_NEURON;

		m_weight[i] = m_neuron_value[0] + n;
		m_weight_step[i] = m_weight[i] + m_dimensions[i] * m_dimensions[i + 1];


		n += m_dimensions[i] * m_dimensions[i + 1] * PARAMETER_COUNT_WEIGHT;
	}
	
	//			3. assign random values //utils::random_fixed(NN::neuron_range.first, NN::neuron_range.second
	
	for (int i = 0; i < m_layer_count; i++) //randomize biases, zero all other parameters
	{
		for (int j = 0; j < m_dimensions[i]; j++) 
		{
			m_neuron_value[i][j] = 0;
			m_neuron_bias[i][j] = math::random(BIAS_INIT_RANGE);
			m_neuron_gradient[i][j] = 0;
			m_neuron_step[i][j] = 0;
		}
	}

	for (int i = 0; i < m_layer_count - 1; i++) // randomize weights, zero nudges
	{
		for (int total_weights = m_dimensions[i] * m_dimensions[i + 1], j = 0; j < total_weights; j++)
		{
			m_weight[i][j] = math::random(WEIGHT_INIT_RANGE);
			m_weight_step[i][j] = 0;
		}
	}
	
	logger::consoleLog("Initialized network " + std::to_string(m_id), INFO);
	logger::consoleLog("Allocated " + std::to_string(m_memory_size) + " * " + std::to_string(sizeof(float)) + " bytes of memory.", SUB_INFO);
	logger::consoleLog("Total initialized memory: " + std::to_string(get_total_memory()) + " bytes", SUB_INFO);
}

NN::~NN() {
	_aligned_free(m_neuron_value[0]);
	delete[] m_neuron_value;
	delete[] m_weight;
	logger::consoleLog("Released network " + std::to_string(m_id), INFO);
}
