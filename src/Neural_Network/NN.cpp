#include "NN.h"
#include "../utilities/util.h"

#include <string>

const int& NN::get_count() 
{
	return count;
}

const std::vector<int>& NN::get_dimentions() 
{
	return m_dimensions;
}

const int& NN::get_id() 
{
	return m_id;
}

const int& NN::get_total_memory() 
{
	return total_memory;
}



void NN::print_memory() 
{
	for (int i = 0; i < m_memory_size; i++) 
	{
		logger::consoleLog(std::to_string(*(m_neuron_value[0] + i)) + ", ");
	}
	logger::newLine();
}

void NN::forward_pass() 
{
	return;
}
