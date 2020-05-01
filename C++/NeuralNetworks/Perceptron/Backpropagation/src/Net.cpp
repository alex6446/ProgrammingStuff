#include "Net.h"
#include <cmath>
#include <iostream>
#include <random>

Net::Net (int* topology, int layers, bool bias) 
	: bias(bias), inputs(nullptr), outputs(nullptr)
{
	srand(time(NULL));
	this->layers = layers;
	this->topology = new int[this->layers];
	for (int i = 0; i < this->layers; i++) 
		this->topology[i] = topology[i] + (int)this->bias;

	this->neurons = new Neuron*[this->layers];
	for (int i = 0; i < this->layers; i++) {
		this->neurons[i] = new Neuron[this->topology[i]];
		for (int j = 0; j < this->topology[i]; j++) {
			if (!i || (this->bias && j == this->topology[i]-1))
				this->neurons[i][j].init(0, nullptr);
			else
				this->neurons[i][j].init(this->topology[i-1], this->neurons[i-1]);
			std::cout << std::endl;
		}
	}
	this->result = new double[this->topology[this->layers-1]-(int)this->bias];
}

Net::~Net () {
	for (int i = 0; i < this->layers; i++)
		delete[] this->neurons[i];
	delete[] this->neurons;

	delete[] this->topology;

	this->cleanLearningData();

	delete[] this->result;
}

void Net::setLearningData (double** inputs, double** outputs, int size) {
	this->cleanLearningData();
	this->size = size;
	this->inputs = new double*[this->size];
	this->outputs = new double*[this->size];
	for (int i = 0; i < this->size; i++) {
		this->inputs[i] = new double[this->topology[0]-(int)this->bias];
		for (int j = 0; j < this->topology[0]-(int)this->bias; j++)
			this->inputs[i][j] = inputs[i][j];
		this->outputs[i] = new double[this->topology[this->layers-1]-(int)this->bias];
		for (int j = 0; j < this->topology[this->layers-1]-(int)this->bias; j++)
			this->outputs[i][j] = outputs[i][j];
	}
}

void Net::setLearningData (double* data, int size) {
	this->cleanLearningData();
	this->size = size / (this->topology[0]-(int)this->bias + 
						this->topology[this->layers-1]-(int)this->bias); // CHANGES IF YOU CHANGE DATA STRUCTURE!
	this->inputs = new double*[this->size];
	this->outputs = new double*[this->size];
	int index = 0;
	for (int i = 0; i < this->size; i++) {
		this->inputs[i] = new double[this->topology[0]-(int)this->bias];
		for (int j = 0; j < this->topology[0]-(int)this->bias; j++) {
			this->inputs[i][j] = data[index++];
		}
		this->outputs[i] = new double[this->topology[this->layers-1]-(int)this->bias];
		for (int j = 0; j < this->topology[this->layers-1]-(int)this->bias; j++) {
			this->outputs[i][j] = data[index++];
		}
	}
}

void Net::startLearning (double accuracy) {
	double error; // current error
	int index = 0; // index of dataset
	int count = 0;
	do {
		error = 0;
		for (int k = 0; k < this->size; k++) {
			for (int i = 0; i < this->topology[0]-(int)bias; i++)
				this->neurons[0][i].setOut(this->inputs[index][i]);
			for (int i = 1; i < this->layers; i++) 
				for (int j = 0; j < this->topology[i]-(int)this->bias; j++)
					this->neurons[i][j].forwardPropagation();

			for (int i = 0; i < this->topology[this->layers-1]-(int)this->bias; i++) {
				this->neurons[this->layers-1][i].addDelta(this->neurons[this->layers-1][i].getOut() - outputs[index][i]);
				error += 0.5 * pow(this->neurons[this->layers-1][i].getOut() - outputs[index][i], 2);
			}

			for (int i = this->layers-1; i > 0; i--) 
				for (int j = 0; j < this->topology[i]-(int)this->bias; j++)
					this->neurons[i][j].backPropagation();
			index = ++index % this->size;
			count++;
		}
		error /= (double)this->size;
		//std::cout << "Error: " << error << " " << index << std::endl;
	} while (error > accuracy);
	std::cout << "Total: " << count << std::endl;
}

void Net::startLearning (int iterations) {
	if (!(outputs && inputs)) return;
	double error; // current error
	int index = 0; // index of dataset
	for (int i = 0; i < iterations; i++) {
		error = 0;
		for (int i = 0; i < this->topology[0]-(int)bias; i++)
			this->neurons[0][i].setOut(this->inputs[index][i]);
		for (int i = 1; i < this->layers; i++) 
			for (int j = 0; j < this->topology[i]-(int)this->bias; j++)
				this->neurons[i][j].forwardPropagation();

		for (int i = 0; i < this->topology[this->layers-1]-(int)this->bias; i++) {
			this->neurons[this->layers-1][i].addDelta(this->neurons[this->layers-1][i].getOut() - outputs[index][i]);
			error += 0.5 * pow(this->neurons[this->layers-1][i].getOut() - outputs[index][i], 2);
		}

		for (int i = this->layers-1; i > 0; i--) 
			for (int j = 0; j < this->topology[i]-(int)this->bias; j++)
				this->neurons[i][j].backPropagation();
		
		index = ++index % this->size;

		//std::cout << "Error: " << error << " " << index << std::endl;
	}
}

double* Net::compute (double* input) {
	for (int i = 0; i < this->topology[0]-(int)bias; i++)
		this->neurons[0][i].setOut(input[i]);
	for (int i = 1; i < this->layers; i++) 
		for (int j = 0; j < this->topology[i]-(int)this->bias; j++)
			this->neurons[i][j].forwardPropagation();

	for (int i = 0; i < this->topology[this->layers-1]-(int)this->bias; i++) {
		result[i] = this->neurons[this->layers-1][i].getOut();
	}
	return result;
}

void Net::cleanLearningData () {
	if (this->inputs) {
		for (int i = 0; i < this->size; i++) 
			delete[] this->inputs[i];
		delete[] this->inputs;
	}

	if (this->outputs) {
		for (int i = 0; i < this->size; i++) 
			delete[] this->outputs[i];
		delete[] this->outputs;
	}
}

void Net::reset () {
	for (int i = 1; i < this->layers; i++) 
		for (int j = 0; j < this->topology[i]-(int)this->bias; j++)
			this->neurons[i][j].reset();
}