#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

bool isNum (char digit) {
	return (digit > 47 && digit < 58) || digit == '.';
}

bool isNum (string number) {
	for (auto digit : number)
		if (!isNum(digit))
			return false;
	return true;
}

bool isBinOp (string op) {
	string OpList[] = {"+", "*", "/", "^"};
	for (auto i : OpList)
		if (i == op)
			return true;
	return false;
}

bool isUnOp (string op) {
	string OpList[] = {"-", "sin", "cos", "sqrt"};
	for (auto i : OpList)
		if (i == op) 
			return true;
	return false;
}

bool MatchOp (string op) {
	if (isBinOp(op)) return true;
	if (isUnOp(op)) return true;
	if (op == "(" || op == ")") return true;
	return false;
}

double UnCount (double a, string op) {
	if (op == "-") return -a;
	if (op == "sin") return sin(a*0.01745329251);
	if (op == "cos") return cos(a*0.01745329251);
	if (op == "sqrt") return sqrt(a);
	return 0;
}

double BinCount (double a, double b, string op) {
	if (op == "+") return a + b;
	if (op == "*") return a * b;
	if (op == "/") return a / b;
	if (op == "^") return pow(a, b);
	return 0;
}

int Order (string op) {
	if (op == "+") return 3;
	if (op == "*") return 2;
	if (op == "/") return 2;
	if (op == "^") return 1;
	return 0;
}

vector<string> Normalize (string problem) {
	vector<string> normalized;
	string buffer;
	int brackets = 0;

	for (int i = 0; i < problem.size();) {
		if (problem[i] == ' ') {
			i++;
			continue;
		}
		if (isNum(problem[i])) {
			while (isNum(problem[i])) {
				buffer.push_back(problem[i++]);
				if (i >= problem.size())
					break;
			}
		} else {
			while (!MatchOp(buffer)) {
				if (i >= problem.size()) {
					cout << " [ERROR]: Неизвестный оператор!" << endl;
					break;
				}
				buffer.push_back(problem[i++]);
			}
		}
		if (!normalized.empty()) {
			if (isNum(normalized.back()) && buffer == "-") normalized.push_back("+");
			else if (normalized.back() == ")" && buffer == "-") normalized.push_back("+");
			else if (isNum(normalized.back()) && buffer == "(") normalized.push_back("*");
			else if (normalized.back() == ")" && buffer == "(") normalized.push_back("*");
			else if (normalized.back() == ")" && isNum(buffer)) normalized.push_back("*");
			else if (isNum(normalized.back()) && isUnOp(buffer)) normalized.push_back("*");
			else if (normalized.back() == ")" && isUnOp(buffer)) normalized.push_back("*");
		}
		if (buffer == "(") brackets++;
		else if (buffer == ")") brackets--;
		if (normalized.empty()) normalized.push_back(buffer);
		else if (!(normalized.back() == buffer && isBinOp(buffer))) normalized.push_back(buffer);
		buffer.clear();
	}
	while (brackets-- > 0) normalized.push_back(")");
	return normalized;
}

double Solve (string problem) {
	vector<string> normalized =  Normalize(problem);
	vector<double> numbers;
	vector<string> operations;
	double a;
	double b;

	for (string object : normalized) {
		if (isNum(object)) {
			numbers.push_back(stod(object));
		} else if (isUnOp(object)) {
			operations.push_back(object);
		} else if (isBinOp(object)) {
			if (operations.empty() || operations.back() == "(") {
				operations.push_back(object);
			} else {
				while (Order(object) >= Order(operations.back()) && operations.back() != "(") {
					if (isUnOp(operations.back())) {
						a = numbers.back();
						numbers.pop_back();
						numbers.push_back(UnCount(a, operations.back()));
						operations.pop_back();
					} else if (isBinOp(operations.back())) {
						b = numbers.back();
						numbers.pop_back();
						a = numbers.back();
						numbers.pop_back();
						numbers.push_back(BinCount(a, b, operations.back()));
						operations.pop_back();
					}
					if (operations.empty()) break;
				}
				operations.push_back(object);
			}
		} else if (object == "(") {
			operations.push_back(object);
		} else if (object == ")") {
			while (operations.back() != "(") {
				if (isUnOp(operations.back())) {
					a = numbers.back();
					numbers.pop_back();
					numbers.push_back(UnCount(a, operations.back()));
					operations.pop_back();
				} else if (isBinOp(operations.back())) {
					b = numbers.back();
					numbers.pop_back();
					a = numbers.back();
					numbers.pop_back();
					numbers.push_back(BinCount(a, b, operations.back()));
					operations.pop_back();
				}
			}
			operations.pop_back();
		}
	}

	while (!operations.empty()) {
		if (isUnOp(operations.back())) {
			a = numbers.back();
			numbers.pop_back();
			numbers.push_back(UnCount(a, operations.back()));
			operations.pop_back();
		} else if (isBinOp(operations.back())) {
			b = numbers.back();
			numbers.pop_back();
			a = numbers.back();
			numbers.pop_back();
			numbers.push_back(BinCount(a, b, operations.back()));
			operations.pop_back();
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
		/*for (string i : Normalize(problem))
			cout << " " << i << " ";
		cout << endl;*/
		cout << " Ответ: " << Solve(problem) << endl << endl;
	}
	return 0;
}

// 1+2(3+4/2-(1+2))2+1
// (12-(35/(12-7)+7)+28)/13
// 2(3(8-5)0.5*0.5
// 2(3(8-5)-0.5*-0.5
// 2^-sqrt25
// -(cossqrt3600
