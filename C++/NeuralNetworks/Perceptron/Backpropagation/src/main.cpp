#include <iostream>
#include "Net.h"

using namespace std;

int main () {

	// Init topology
	int layers = 3;
	int topology[] = { 2, 2, 1 };
	Net net(topology, layers);

	// Init dataset
	int size = 8;//14
	double **inputs = new double*[size];
	double **outputs = new double*[size];
	for (int i = 0; i < size; i++) {
		inputs[i] = new double[2];
		outputs[i] = new double[1];
	}

	inputs[0][0] = 3;
	inputs[0][1] = 1.5;
	outputs[0][0] = 1;

	inputs[1][0] = 2;
	inputs[1][1] = 1;
	outputs[1][0] = 0;

	inputs[2][0] = 4;
	inputs[2][1] = 1.5;
	outputs[2][0] = 1;

	inputs[3][0] = 3;
	inputs[3][1] = 1;
	outputs[3][0] = 0;//0

	inputs[4][0] = 3.5;
	inputs[4][1] = 1;
	outputs[4][0] = 1;

	inputs[5][0] = 2;
	inputs[5][1] = 0.5;
	outputs[5][0] = 0;

	inputs[6][0] = 5.5;
	inputs[6][1] = 1;
	outputs[6][0] = 1;

	inputs[7][0] = 1;
	inputs[7][1] = 1;
	outputs[7][0] = 0;//0


	/*inputs[0][0] = 3;
	inputs[0][1] = 1.5;
	outputs[0][0] = 1;

	inputs[1][0] = 2;
	inputs[1][1] = 1;
	outputs[1][0] = 0;

	inputs[2][0] = 4;
	inputs[2][1] = 1.5;
	outputs[2][0] = 1;

	inputs[3][0] = 1.5;
	inputs[3][1] = 0.5;
	outputs[3][0] = 0;//0

	inputs[4][0] = 3.5;
	inputs[4][1] = 0.5;
	outputs[4][0] = 1;

	inputs[5][0] = 2;
	inputs[5][1] = 0.5;
	outputs[5][0] = 0;

	inputs[6][0] = 2;
	inputs[6][1] = 2;
	outputs[6][0] = 1;

	inputs[7][0] = 1.5;
	inputs[7][1] = 1;
	outputs[7][0] = 0;//0

	inputs[8][0] = 1;
	inputs[8][1] = 1.5;
	outputs[8][0] = 1;

	inputs[9][0] = 0;
	inputs[9][1] = 1;
	outputs[9][0] = 1;

	inputs[10][0] = 1;
	inputs[10][1] = 0.5;
	outputs[10][0] = 1;//0
	
	inputs[11][0] = 1;
	inputs[11][1] = 1;
	outputs[11][0] = 1;//0

	inputs[12][0] = 0.5;
	inputs[12][1] = 0;
	outputs[12][0] = 1;//0
	
	inputs[13][0] = 1.5;
	inputs[13][1] = 0;
	outputs[13][0] = 1;//0
*/
	net.setLearningData(inputs, outputs, size);
	net.startLearning(0.0001);

	double *input = new double[2];
	input[0] = 2.5;
	input[1] = 0.5;
	std::cout << net.compute(input)[0] << endl;

	for (float i = 0; i < 5; i+=0.2) {
		for (float j = 0; j < 5; j+=0.2) {
			input[0] = j;
			input[1] = 4-i;
			if (net.compute(input)[0] < 0.5)
				cout << "*";
			else
				cout << "#";
		}
		cout << endl;
	}

} 
