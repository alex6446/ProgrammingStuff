#include "NeuralNet/Neuron.h"
#include <random>
#include <cmath>

#include <iostream>

Neuron::Neuron () 
	: out(1), weights(nullptr)
{}

Neuron::~Neuron () {
	delete[] this->weights;
}

void Neuron::init (int T, Neuron* neurons) {
	this->T = T;
	this->neurons = neurons;
	this->delta = 0;

	this->weights = new double[T];
	for (int i = 0; i < T; i++){
		this->weights[i] = -2.0 + (double)rand() / RAND_MAX * 4.0;
		std::cout << this->weights[i] << std::endl;
	}
}


void Neuron::addDelta (double value) {
	this->delta += value;
}

double Neuron::getOut () {
	return this->out;
}

void Neuron::setOut (double value) {
	this->out = value;
}

void Neuron::forwardPropagation () {
	double net = 0;
	for (int i = 0; i < this->T; i++) 
		net += this->weights[i] * this->neurons[i].getOut();
	this->out = sigmoid(net);
}

void Neuron::backPropagation () {
	this->delta *= this->out * (1 - this->out);
	//std::cout << delta << std::endl;
	double error;
	for (int i = 0; i < this->T; i++) {
		this->neurons[i].addDelta(this->delta * this->weights[i]);
		error = this->delta * this->neurons[i].getOut();
		this->weights[i] -= 0.5 * error;
	}
	this->delta = 0;
}

double Neuron::sigmoid (double net) {
	return 1 / (1 + exp(-net));
}

void Neuron::reset () {
	for (int i = 0; i < T; i++)
		this->weights[i] = -2.0 + (double)rand() / RAND_MAX * 4.0;
}
