#include "Neural_Network/NeuralNet.h"
#include "utilities/util.h"


int main() 
{
	log_config::setLogLevel(DEBUG);
	
	NN net({2,4,2});

	net.print_memory();
		
}
