#include <iostream>
#include <vector>

using namespace std;

bool Is_number (char digit) {
	switch (digit) {
		case '0':
		case '1': return true;
		default: return false;
	}
}

int Get_number (char digit) {
	if (digit == '0') return 0;
	else return 1;
}

bool Is_operation (char digit) {
	switch (digit) {
		case '!':
		case '|': 
		case '>': 
		case '~': 
		case '<': 
		case 'v':  
		case '*': return true;
		default : return false;
	}
}

int Priority (char operation) {
	switch (operation) {
		case '|': return 1;
		case '~': return 2;
		case '>': 
		case '<': return 3;
		case 'v': return 4; 
		case '*': return 5;
		case '!': return 6;
		default : return 0;
	}
}

double Count (double a, double b, char operation) {
	switch (operation) {
		case '|': if (!(a + b)) return 1; else return 0;
		case '>': if (a == 1 && b == 0) return 0; else return 1;
		case '<': if (a == 0 && b == 1) return 0; else return 1;
		case '~': if (a == b) return 1; else return 0;
		case '*': return a * b;
		case 'v': if (a + b) return 1; else return 0;
		default : return 0;
	}
}

string Normalize (string problem) {
	string normalized;
	for (int i = 0; i < problem.length(); i++) {
		if (problem[i] == ' ')
			continue;
		if (i)
			if (Is_number(problem[i]) && Is_number(problem[i-1])
				|| (problem[i] == '(' && Is_number(problem[i-1]))
				|| (problem[i-1] == ')' && Is_number(problem[i]))
				|| (problem[i-1] == ')' && problem[i] == '('))
				normalized.append("*");
		normalized.append(string(1, problem[i]));
	}
	/*if (Is_number(problem[i]) && Is_number(problem[i-1])
			|| (problem[i] == '(' && Is_number(problem[i-1]))
			|| (problem[i-1] == ')' && Is_number(problem[i])) 
			|| (problem[i-1] == ')' && problem[i] == '(')
			|| (problem[i] == '!' && Is_number(problem[i-1]))
			|| (problem[i] == '!' && problem[i-1] == ')'))*/
	return normalized;
}

int Solve (string problem) {

	string normalized =  Normalize(problem);
	vector<int> numbers;
	vector<char> operations;

	for (char object : normalized) {
		if (Is_number(object)) {
			numbers.push_back(Get_number(object));
		} else if (Is_operation(object)) {
			if (operations.empty() || operations.back() == '(') {
				operations.push_back(object);
			} else {
				while (Priority(object) <= Priority(operations.back()) && operations.back() != '(') {
					char operation = operations.back();
					operations.pop_back();
					int a = numbers.back();
					numbers.pop_back();
					if (operation == '!')
						numbers.push_back(!a);
					else {
						int b = numbers.back();
						numbers.pop_back();
						numbers.push_back(Count(b, a, operation));
					}

					if (operations.empty())
						break;
				}
				operations.push_back(object);
			}
		} else if (object == '(') {
			operations.push_back(object);
		} else if (object == ')') {
			while (operations.back() != '(') {
				char operation = operations.back();
				operations.pop_back();
				int a = numbers.back();
				numbers.pop_back();
				if (operation == '!')
					numbers.push_back(!a);
				else {
					int b = numbers.back();
					numbers.pop_back();
					numbers.push_back(Count(b, a, operation));
				}
			}
			operations.pop_back();
		}
	}

	while (!operations.empty()) {
		char operation = operations.back();
		operations.pop_back();
		int a = numbers.back();
		numbers.pop_back();
		if (operation == '!')
			numbers.push_back(!a);
		else {
			int b = numbers.back();
			numbers.pop_back();
			numbers.push_back(Count(b, a, operation));
		}
	}
	return numbers.back();
}

int main () {
	setlocale(LC_ALL, "Russian");
	cout << "\t\t\t ********* Калькулятор ********* \n\n" << endl; 

	string problem;
	while (true) {
		cout  << endl << " Введите пример: ";
		getline (cin, problem);
		cout << " Ответ: " << Solve(problem) << endl << endl;
		/*for (string i : Normalize(problem))
			cout << i << " ";*/
	}
	return 0;
}

// (0~0)v((0>0)|!0)
// (0~0)v((0>0)|!1)
// (0~1)v((1>0)|!0)
// (0~1)v((1>0)|!1)
// (1~0)v((0>1)|!0)
// (1~0)v((0>1)|!1)
// (1~1)v((1>1)|!0)
// (1~1)v((1>1)|!1)

// (0~0)v(0v1)
// (1~0)(0>1)
