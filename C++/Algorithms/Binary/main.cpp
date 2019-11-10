#include <iostream>
#include <fstream>
using namespace std;

int main () {

	int x = 12;
	int a;

	fstream file("binary.bin", ios::binary | ios::out);

	ofstream out("binary.bin", ios::binary);
	out.write((char*)&x, sizeof(x));
	out.close();
	ifstream in("binary.bin", ios::binary);
	in.read((char*)&a, sizeof(a));
	cout << a;
}


