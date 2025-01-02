#include <string>

#include "NeuralNet.h"
#include "../utilities/util.h"

unsigned int NN::count = 0;
unsigned int NN::total_memory = 0;


void NN::print_memory() const
{
	for (int i = 0; i < m_total_value_count; i++) 
	{
		logger::consoleLog(std::to_string(*(m_input + i)) + ", ");
	}
	logger::newLine();
}
