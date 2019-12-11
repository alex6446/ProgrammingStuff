#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>

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
		case '>': 
		case '~': return 2;
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
		if (!normalized.empty())
			if ((Is_number(normalized.back()) || normalized.back() == ')') && 
				(Is_number(problem[i]) || problem[i] == '(' || problem[i] == '!'))
				normalized.append("*");

		normalized.append(string(1, problem[i]));
	}
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

string Translate (int index, string variables) {
	string translated(variables.length(), '0');
	int number = index;
	int i = variables.length()-1;
	do {
		if (number%2)
			translated[i] = '1';
		else translated[i] = '0';
		i--;
	} while (number /= 2);
	return translated;
}

string Substitute (string problem, string variables, string translated) {
	string unique;
	int index;
	for (auto i : problem) {
		index = variables.find(i);
		if (index == string::npos)
			unique.append(string(1, i));
		else
			unique.append(string(1, translated[index]));
	}
	return unique;
}

int main () {
	setlocale(LC_ALL, "Russian");
	cout << "\t\t\t ********* Булева Алгебра ********* \n\n" << endl; 

	string variables;
	string problem;
	istringstream stream;
	string translated;
	string substituted;
	
	while (true) {
		cout << " Введите символы переменных: ";
		getline (cin, variables);
		cout << " Введите задание: ";
		getline (cin, problem);
		cout << " Результат: " << endl << endl;
		cout << " " << variables << "\tf\t" << problem << endl;
		for (int i = 0; i < pow(2, variables.length()); i++) {
			translated =  Translate(i, variables);
			substituted = Substitute(problem, variables, translated);
			cout << " " << translated << "\t";
			cout << Solve(substituted);
			cout << "\t" << substituted;
			cout << endl;
		}
		cout << endl;
	}
	return 0;
}

