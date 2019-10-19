#include <iostream>

using namespace std;

int main() {

	const int N = 64;
	unsigned long long result = 1, pow = 1;

	for (int i = 1; i <= 64; i++) {
		cout << "На клетке " << i << " находится " << pow << " зёрен!" << endl;
		pow = 1;
		for (int j = 0; j < i; j++)
			pow *= 2;
		result += pow;
	}

}