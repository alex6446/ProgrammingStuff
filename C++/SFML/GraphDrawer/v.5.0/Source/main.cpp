#include <iostream>
#include "Graph.h"

using namespace std;

int main () {

	Graph net(800, 520);
	net.setTheme("Azul");
	int i = 0;
	while (net.run()) {
		net.update();
		net.draw();
	}

}
