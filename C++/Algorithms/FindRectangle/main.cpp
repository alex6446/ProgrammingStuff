#include <iostream>

using namespace std;

int main () {

	int N, M;
	cin >> N >> M;

	int **arr = new int*[N];
	for (int i = 0; i < N; i++)
		arr[i] = new int[M];

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> arr[i][j];

	int max = 0;
	int start[2] = {0, 0};
	int end[2] = {0, 0};

	bool complete;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {

			for (int k = i; k < N; k++) {
				complete = true;
				for (int l = j; l < M; l++)	{

					for (int m = i; m <= k; m++) {
						for (int n = j; n <= l; n++) {
							complete = arr[m][n];
							if (!complete)
								break;
						}
						if (!complete)
							break;
					}
					if (complete) {
						int square = (k-i+1)*(l-j+1); 
						if (square > max) {
							max = square;
							start[0] = i;
							start[1] = j;
							end[0] = k;
							end[1] = l;
						}
					}

				}	
			}	

		}
	}

	cout << endl << "Square: " << max << endl;
	cout << "Coordinates: arr[" << start[0] << "][" << start[1] << "] ";
	cout << "arr[" <<  end[0] << "][" << end[1] << "]" << endl;
}

/*
4 5
0 1 1 1 1
0 1 1 1 0
0 1 1 0 0
1 1 1 0 0
*/
