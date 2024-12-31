#pragma once
#include "Config.h"
#include <vector>

constexpr unsigned int PARAMETER_COUNT_NEURON = 4;
constexpr unsigned int PARAMETER_COUNT_WEIGHT = 2;

class NN 
{
public:

	NN(const std::vector<unsigned int>&);
	~NN();

	void print_memory() const;
	
	[[nodiscard]] static inline const unsigned int get_count() noexcept { return count; }
	[[nodiscard]] static inline const unsigned int get_total_allocated_memory() noexcept { return total_memory; }
	[[nodiscard]] inline const std::vector<unsigned int>& get_dimentions() const noexcept { return m_dimensions; }
	[[nodiscard]] inline const unsigned int get_id() const noexcept { return m_id; }
	[[nodiscard]] inline const unsigned int get_memory_size() const noexcept { return m_memory_size; }

private:

	void fwrdProp();
	void backProp();

	static unsigned int count;
	static unsigned int total_memory;
	const std::vector<unsigned int> m_dimensions;
	const unsigned int m_id;
	unsigned int m_memory_size;
	unsigned int m_layer_count;

	float** m_neuron_value;
	float** m_neuron_bias;
	float** m_neuron_gradient;
	float** m_neuron_step;

	float** m_weight;
	float** m_weight_step;
};

