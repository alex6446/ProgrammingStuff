#include <iostream>
#include <vector>

using namespace std;

////////// IS NUMBER ////////////////////////////////////////////

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

////////// PRIORITY /////////////////////////////////////////////

int Priority (char operation) {
	switch (operation) {
		case '+':
		case '-': return 1; 
		case '*':
		case '/': return 2;
		default : return 0;
	}
}

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

////////// NORMALIZE ////////////////////////////////////////////

vector<string> Normalize (string problem) {

	vector<string> normalized;
	string buffer;
	bool InNum;
	int brackets = 0;
	
	if (Is_number(problem[0]) || problem[0] == '-')
		InNum = true;
	else
		InNum = false;

	for (char digit : problem) {
		if (digit == ' ')
			continue;
		if (!(Is_number(digit) && InNum) && !buffer.empty()) {
			if (buffer == "(") {
				brackets++;
				if (!normalized.empty())
					if (Is_number(normalized.back()))
						normalized.push_back("*");
			} else if (buffer == ")")
				brackets--;
			normalized.push_back(buffer);
			buffer.clear();
			if (Is_number(digit) && !InNum) {
				InNum = true;
				if (!normalized.empty())
					if (normalized.back() == ")")
						normalized.push_back("*");
			}
			else if (!Is_number(digit) && InNum)
				InNum = false;
			else if (digit == '-' && normalized.back() != ")")
				InNum = true;
		}
		buffer.push_back(digit);
	}
	if (buffer == "(")
		brackets++;
	else if (buffer == ")")
		brackets--;
	normalized.push_back(buffer);

	while (!Is_number(normalized.back()) && normalized.back() != ")")
		normalized.pop_back();
	while (brackets > 0) {
		normalized.push_back(")");
		brackets--;
	}

	return normalized;
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

//1+2(3+4/2-(1+2))2+1
//(12-(35/(12-7)+7)+28)/13
//2(3(8-5)0.5*0.5
//2(3(8-5)-0.5*-0.5