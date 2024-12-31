#include "Neural_Network/NN.h"
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
	log_config::setLogLevel(INFO);
	
	timer::startTimer();
	NN net({2,4,2});
	timer::endTimer();

	logger::consoleLog(std::to_string(timer::getElapsedSeconds()), INFO);

	net.print_memory();
		
}
