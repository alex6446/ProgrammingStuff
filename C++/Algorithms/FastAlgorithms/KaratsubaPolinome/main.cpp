#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <array>

using namespace std;
//extern wostream wcout;

void input (vector<int> &A, vector<int> &B) {
	int number;
	string line;
	istringstream stream;

	cout << "Enter first polynome: ";
	getline(cin, line);
    stream.str(line);
    while (stream >> number)
        A.push_back(number);

    cout << "Enter second polynome: ";
    getline(cin, line);
    stream.clear();
    stream.str(line);
    while (stream >> number)
        B.push_back(number);

    while (A.size() < B.size()) A.push_back(0);
    while (B.size() < A.size()) B.push_back(0);
}

void print (vector<int> A) {
	for (auto i : A) cout << i << " ";
	cout << endl;
}

vector<int> KaratsubaPolinome (vector<int> A, vector<int> B) {
	int n = A.size();
	int c = 2 * n - 2;
	vector<int> C;

	vector<int> Di;
	for (int i = 0; i < n; i++)
		Di.push_back(A[i] * B[i]);
	
	vector<int> Dst;
	vector<array<int, 2>> Ist;
	for (int i = 1; i < c; i++) {
		for (int s = 0; s < n; s++) {
			for (int t = 1; t < n; t++) {
				if (s < t && s + t == i) {
					Dst.push_back((A[s] + A[t]) * (B[s] + B[t]));
					Ist.push_back({s, t});
				} else if (s + t > i) break;
			}
			if (s >= i) break;
		}
	}

	int buffer;
	int index = 0;
	for (int i = 0; i <= c; i++) {
		if (!i) C.push_back(Di[0]);
		else if (i == c) C.push_back(Di[n-1]);
		else {
			buffer = 0;
			while (Ist[index][0]+Ist[index][1] == i) {
				buffer += Dst[index];
				buffer -= Di[Ist[index][0]] + Di[Ist[index][1]];
				if (index++ >= Ist.size()) break;
			}
			if (!(i & 1)) buffer += Di[i / 2];
			C.push_back(buffer);
		}
	}
	return C;
}

int main () {

	vector<int> A;
	vector<int> B;
	vector<int> C;

	input(A, B);

	print(A);
	print(B);	

	C = KaratsubaPolinome(A, B);
	print(C);
}

