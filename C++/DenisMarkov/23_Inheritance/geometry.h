#pragma once

#include <iostream>
#include <initializer_list>
#include <array>

using namespace std;

class Figure {
private:
	int 	V;
	int 	E;
	double	**Vertices;
	double 	*Edges;
	char	*Color;
public:
	Figure();
	Figure(initializer_list<double> vertices, initializer_list<double> edges, char* color="black");
	void 	Print();
	void	SetValues(initializer_list<double> vertices, initializer_list<double> edges, char* color="black");
	void	SetValues(initializer_list<double> vertices, double edges, char* color="black");
};

class Square : public Figure {
private:
	double 	Area;
	double	Diagonal; 	
public:
	Square();
	Square(initializer_list<double> vertices, double edge, char* color="black");
	double 	GetArea();
	double 	GetDiagonal();
	/*friend void operator>>(ifstream&, Square&);*/
};

class Circle : public Figure {
private:
	double Radius;
	double Center[2];
public:
	Circle();
	Circle(array<double, 2> center, double radius, char* color="black");
	double 	GetArea();
	void 	PrintCircle();
	friend void operator>>(ifstream&, Circle&);
};