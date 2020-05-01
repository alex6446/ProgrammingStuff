#pragma once

#include "Neuron.h"

class Net {
private:

	Neuron** neurons; // Layers of neurons
	int* topology; // Number of neurons in each layer
	int layers; // Numer of layers
	bool bias;

	double** inputs;
	double** outputs;
	int size;

public:

	Net (int* topology, int layers, bool bias = true);
	~Net ();

	void setLearningData (float* data, int size);
	void startLearning (int iterations);
	void reset ();

	double* compute (double* input);

private:

	void cleanLearningData ();
};
