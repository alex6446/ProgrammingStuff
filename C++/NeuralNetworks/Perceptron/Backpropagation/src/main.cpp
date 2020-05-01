#include <iostream>
#include "Net.h"

using namespace std;

int main () {

	// Init topology
	int topology[] = { 2, 2, 1 };
	int layers = sizeof(topology) / sizeof(int);
	Net net(topology, layers);

	// Init dataset
	double data[] = {
		3,   1.5, 1,  
		2,   1,   0,  
		4,   1.5, 1,  
		3,   1,   0,
		3.5, 1,   1,
		2,   0.5, 0, 
		5.5, 1,   1,
		1,   1,   0  
	};	

	/*double data[] = { 
		3, 1.5, 1,
 		2, 1, 0,
 		4, 1.5, 1,
 		1.5, 0.5, 0,//0
 		3.5, 0.5, 1,
 		2, 0.5, 0,
 		2, 2, 1,
 		1.5, 1, 0,//0
 		1, 1.5, 1,
 		0, 1, 1,
 		1, 0.5, 1,//0
	 	1, 1, 1,//0
 		0.5, 0, 1,//0
	 	1.5, 0, 1//0
	};*/

	int size = (
		sizeof(data) / sizeof(data[0]) / 
		(topology[0] + topology[layers-1])	
	); 

	net.setLearningData(data, size);
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
