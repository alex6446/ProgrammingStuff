#include <iostream>

using namespace std;

class Graph {
private:
	int N;
	float **my_graph;
public:
	Graph () {
		N = 0;
		my_graph = nullptr;
	}
	Graph (int n) {
		N = n;
		my_graph = new float*[N];
		for (int i = 0; i < N; i++) {
			my_graph[i] = new float[N];
			for (int j = 0; j < N; j++)
				my_graph[i][j] = -1;
		}
	}
	bool add_relation (int from_index, int to_index, float weight) {
		if (my_graph != nullptr)
			my_graph[from_index-1][to_index-1] = weight;
		return true;
	}
	void add_top () {
		float **temp = new float*[N+1];
		for (int i = 0; i < N+1; i++) {
			temp[i] = new float[N+1];
			for (int j = 0; j < N+1; j++)
				temp[i][j] = -1;
		}
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				temp[i][j] = my_graph[i][j];
		my_graph = temp;
		N++;
	}
	void add_tops (int n) {
		float **temp = new float*[N+n];
		for (int i = 0; i < N+n; i++) {
			temp[i] = new float[N+n];
			for (int j = 0; j < N+n; j++)
				temp[i][j] = -1;
		}
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				temp[i][j] = my_graph[i][j];
		my_graph = temp;
		N += n;
	}
	void print_matrix () {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++)
				cout << my_graph[i][j] << " ";
			cout << endl;
		}
	}
};

int main()  {

	Graph graph;

	int tops;
	cin >> tops;
	graph.add_tops(tops);

	int num_calls;
	cin >> num_calls;
	for (int i = 0; i < num_calls; i++) {
		int from_index;
		int to_index;
		float weight;
		cin >> from_index >> to_index >> weight;
		graph.add_relation(from_index, to_index, weight);
	}

	graph.print_matrix();

	return 0;
}
