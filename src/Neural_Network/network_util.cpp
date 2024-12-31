#include "NeuralNet.h"
#include "../utilities/util.h"

#include <string>

unsigned int NN::count = 0;
unsigned int NN::total_memory = 0;


void NN::print_memory() const
{
	for (int i = 0; i < m_memory_size; i++) 
	{
		logger::consoleLog(std::to_string(*(m_neuron_value[0] + i)) + ", ");
	}
	logger::newLine();
}

void NN::fwrdProp() 
{
	return;
}
