#pragma once

class Neuron {
private:

	double out; // Final value
	double delta; // Variable for back propa

	int T; // Topology - ammount of weights, neurons
	double* weights; 
	Neuron* neurons; // Previous neurons

public:

	Neuron ();
	~Neuron ();
	void init (int T, Neuron* neurons);
	void reset ();

	void addDelta (double value);
	double getOut ();
	void setOut (double value);

	void forwardPropagation (); // TODO: do not propagate first layer!
	void backPropagation (); // TODO: make delta 0 in the END!

private:

	double sigmoid (double net); // Activation function
		
};