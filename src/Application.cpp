#include "Neural_Network/NeuralNet.h"
#include "utilities/util.h"

void dot_product_(float* a, float* b, float* res, int lengtha, int lengthres) {
	for (int i = 0; i < lengthres; i++) {
		for (int j = 0; j < lengtha; j++) {
			res[i] += a[j] * b[j + lengtha * i];
		}
	}
}


int main() 
{
	log_config::setLogLevel(DEBUG);
	
	NN net(std::vector<unsigned int>{2,4,2});

	net.print_memory();
		
}
