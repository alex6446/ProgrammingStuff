#include <iostream>
#include <vector>

using namespace std;

////////// FUNCTIONS ////////////////////////////////////////////

double 			Solve (string problem);
vector<string>	Normalize (string problem);
double 			Count (double a, double b, char operation);
int 			Priority (string str);
int 			Priority (char operation);
bool 			Is_operation (string str);
bool 			Is_number (string str);
bool 			Is_number (char digit);

////////// MAIN /////////////////////////////////////////////////

int main () {
	setlocale(LC_ALL, "Russian");
	cout << "\t\t\t ********* Калькулятор ********* \n\n" << endl; 

	string problem;
	while (true) {
		cout << " Введите пример: ";
		getline (cin, problem);
		cout << " Ответ: " << Solve(problem) << endl << endl;
	}
	return 0;
}

////////// SOLVE ////////////////////////////////////////////////

double Solve (string problem) {

	vector<string> normalized =  Normalize(problem);
	vector<double> numbers;
	vector<char> operations;

	for (string object : normalized) {
		if (Is_number(object)) {
			numbers.push_back(stod(object));
		} else if (Is_operation(object)) {
			if (operations.empty() || operations.back() == '(') {
				operations.push_back(object[0]);
			} else {
				while (Priority(object) <= Priority(operations.back()) && operations.back() != '(') {
					double b = numbers.back();
					numbers.pop_back();
					double a = numbers.back();
					numbers.pop_back();
					char operation = operations.back();
					operations.pop_back();
					numbers.push_back(Count(a, b, operation));

					if (operations.empty())
						break;
				}
				operations.push_back(object[0]);
			}
		} else if (object == "(") {
			operations.push_back(object[0]);
		} else if (object == ")") {
			while (operations.back() != '(') {
				double b = numbers.back();
				numbers.pop_back();
				double a = numbers.back();
				numbers.pop_back();
				char operation = operations.back();
				operations.pop_back();
				numbers.push_back(Count(a, b, operation));
			}
			operations.pop_back();
		} else {}
	}

	while (!operations.empty()) {
		double b = numbers.back();
		numbers.pop_back();
		double a = numbers.back();
		numbers.pop_back();
		char operation = operations.back();
		operations.pop_back();
		numbers.push_back(Count(a, b, operation));
	}
	
	return numbers.back();
}

////////// NORMALIZE ////////////////////////////////////////////

vector<string> Normalize (string problem) {

	vector<string> normalized;
	string buffer;
	bool InNum;
	
	if (Is_number(problem[0]) || problem[0] == '-')
		InNum = true;
	else
		InNum = false;

	for (char digit : problem) {
		if (digit == ' ')
			continue;
		if (!(Is_number(digit) && InNum) && !buffer.empty()) {
			normalized.push_back(buffer);
			buffer.clear();
			if (Is_number(digit) && !InNum)
				InNum = true;
			else if (!Is_number(digit) && InNum)
				InNum = false;
			else if (digit == '-')
				InNum = true;
		}
		buffer.push_back(digit);
	}
	normalized.push_back(buffer);

	return normalized;
}

////////// COUNT ////////////////////////////////////////////////

double Count (double a, double b, char operation) {
	switch (operation) {
		case '+': return a + b;
		case '-': return a - b; 
		case '*': return a * b;
		case '/': return a / b;
		default : return 0;
	}
}

////////// PRIORITY /////////////////////////////////////////////

int Priority (string str) {
	char operation = str[0];
	switch (operation) {
		case '+':
		case '-': return 1; 
		case '*':
		case '/': return 2;
		default : return 0;
	}
}

int Priority (char operation) {
	switch (operation) {
		case '+':
		case '-': return 1; 
		case '*':
		case '/': return 2;
		default : return 0;
	}
}

////////// IS OPERATION /////////////////////////////////////////

bool Is_operation (string str) {
	if (str.size() > 1)
		return false;
	char operation = str[0];
	switch (operation) {
		case '+':
		case '-':  
		case '*':
		case '/': return true;
		default : return false;
	}
}

////////// IS NUMBER ////////////////////////////////////////////

bool Is_number (string str) {
	if (str.empty())
		return false;
	if (str[0] == '-' && str.size() == 1)
		return false;
	for (char digit : str)
		if (!Is_number(digit) && digit != '-')
			return false;
	return true;
}

bool Is_number (char digit) {
	switch (digit) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case '.': return true;
		default : return false;
	}
}

//1+2*(3+4/2-(1+2))*2+1
//(12-(35/(12-7)+7)+28)/13
