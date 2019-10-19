/*int min;
for (int i = 0; i < N - 1; i++) {
	min = i;
	for (int j = i+1; j < N; j++)
		if (arr[j] < arr[min])
			min = arr[j];
	swap(arr[i], arr[min]);
}*/

#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

/*struct QuickValues {
	vector<int> buffer_l;
	vector<int> buffer_r;
	//bool first_iter;
	bool next;
	bool i_set;
	bool j_set;
	int l;
	int r;
	int i;
	int j;
	int middle;
};
QuickValues qv;*/

int main () {

	srand(time(NULL));

	vector<int> buffer_l;
	vector<int> buffer_r;
	//bool first_iter;
	bool next;
	bool i_set;
	bool j_set;
	int l;
	int r;
	int i;
	int j;
	int middle;

	int cellNumber = 100;
	next = true;
	i_set = false;
	j_set = false;
	buffer_l.push_back(0);
	buffer_r.push_back(cellNumber-1);

	int* elementIndex = new int[cellNumber];

	for (int k = 0; k < cellNumber; k++)
		elementIndex[k] = rand() % 1000;

	for (int k = 0; k < 1000; k++)
	if (!buffer_l.empty() && !buffer_r.empty()) {
		if (next) {
			l = buffer_l.back();
			r = buffer_r.back();
			i = l;
			j = r;
			middle = elementIndex[(i + j)/2];
			next = false;
		}
		if (i <= j) {
			if (middle > elementIndex[i])
				i++;
			else
				i_set = true;
			if (middle < elementIndex[j])
				j--;
			else
				j_set = true;

			if (i_set && j_set) {
				if (i <= j) {
					swap(elementIndex[i], elementIndex[j]);
					i++;
					j--;
				}
				i_set = false;
				j_set = false;
				//first_iter = false;
			}
		} else {
			//first_iter = true;
			next = true;
			buffer_l.pop_back();
			buffer_r.pop_back();
			if (i < r) {
				buffer_l.push_back(i);
				buffer_r.push_back(r);
			}
			if (j > l) {
				buffer_l.push_back(l);
				buffer_r.push_back(j);
			}
		}
	}

	for (int k = 0; k < cellNumber; k++)
		cout << elementIndex[k] << endl;
	cout << "===================================" << endl;



	return 0;
}