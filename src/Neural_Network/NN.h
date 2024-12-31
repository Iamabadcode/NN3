#pragma once
#include "Config.h"
#include <vector>

constexpr unsigned int PARAMETER_COUNT_NEURON = 4;
constexpr unsigned int PARAMETER_COUNT_WEIGHT = 2;

class NN 
{
public:

	static const int& get_count();
	const std::vector<int>& get_dimentions();
	const int& get_id();
	const int& get_total_memory();
	void print_memory();

	NN(const std::vector<int>&);
	
	~NN();
	void forward_pass();


private:

	static int count;
	static int total_memory;
	const int m_id;
	const std::vector<int> m_dimensions;
	int m_memory_size;
	
	int m_layer_count;

	float** m_neuron_value;
	float** m_neuron_bias;
	float** m_neuron_gradient;
	float** m_neuron_step;

	float** m_weight;
	float** m_weight_step;

};

