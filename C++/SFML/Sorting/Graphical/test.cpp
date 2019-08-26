#include "iostream"

using namespace std;

enum class States { main, selected, highlighted };

int main() {
	
	string color = "orange";
	States state = States::highlighted;

	switch (state) {
		case States::main: color = "orange"; 
			break;
		case States::selected: color = "yellow";
			break;
		case States::highlighted: color = "red";
			break;
	}

	cout << color;


	return 0;
}
