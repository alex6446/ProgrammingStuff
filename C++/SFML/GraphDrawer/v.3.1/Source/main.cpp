#include <iostream>
#include "Graph.h"

using namespace std;

int main () {

	Graph net;

	while (net.run()) {
		net.update();
		net.draw();
	}

}
