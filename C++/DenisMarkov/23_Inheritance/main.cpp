#include <iostream>
#include <fstream>
#include "geometry.h"

using namespace std;

int main() {

	cout << "HelloWorld" << endl;
					
	Square square;
	square.SetValues({ 1, 2,
		   			1, 8,
		   			7, 8,
		   			7, 2 }, 16, "grey");
	square.Print();
	/*cout << square.GetArea() << " " << square.GetDiagonal() << endl;*/

	Circle circle({1, 2}, 12, "orange");
	circle.Print();
	cout << circle.GetArea() << endl;


	ifstream fin("shape.txt");
	fin >> circle;

	circle.Print();
	return 0;
}