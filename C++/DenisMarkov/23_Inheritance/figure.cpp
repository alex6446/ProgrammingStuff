#include <iostream>
#include <initializer_list>
#include <array>
#include <cmath>
#include "geometry.h"
#include <fstream>
using namespace std;

Figure::Figure() {
	Color = "black";
	V = E = 0;
}

Figure::Figure(initializer_list<double> vertices, initializer_list<double> edges, char* color) {
	Color = color;

	V = vertices.size()/2;
	E = edges.size();

	Vertices = new double*[V];
	Edges = new double[E];
	for(int i = 0; i < V; i++)
		Vertices[i] = new double[2];
	
	for(int i = 0; i < V*2; i += 2) {
		Vertices[i/2][0] = vertices.begin()[i];
		Vertices[i/2][1] = vertices.begin()[i+1];
	}
	for(int i = 0; i < E; i++)
		Edges[i] = edges.begin()[i];
}

void Figure::Print() {
	cout << endl << "COLOR\t    ";
	cout << Color << endl;
	cout << "EDGES\t    ";
	for(int i = 0; i < E; i++)
		cout << Edges[i] << " ";
	cout << endl << "COORDINATES X\tY" << endl;

	for(int i = 0; i < V; i++)
		cout << "\t    " << Vertices[i][0] << "\t" << Vertices[i][1] << endl;
}

void Figure::SetValues(initializer_list<double> vertices, initializer_list<double> edges, char* color) {
	Color = color;

	V = vertices.size()/2;
	E = edges.size();

	Vertices = new double*[V];
	Edges = new double[E];
	for(int i = 0; i < V; i++)
		Vertices[i] = new double[2];
	
	for(int i = 0; i < V*2; i += 2) {
		Vertices[i/2][0] = vertices.begin()[i];
		Vertices[i/2][1] = vertices.begin()[i+1];
	}
	for(int i = 0; i < E; i++)
		Edges[i] = edges.begin()[i];
}

void Figure::SetValues(initializer_list<double> vertices, double edge, char* color) {
	Color = color;

	V = vertices.size()/2;
	E = 1;

	Vertices = new double*[V];
	Edges = new double[E];
	for(int i = 0; i < V; i++)
		Vertices[i] = new double[2];
	
	for(int i = 0; i < V*2; i += 2) {
		Vertices[i/2][0] = vertices.begin()[i];
		Vertices[i/2][1] = vertices.begin()[i+1];
	}
	Edges[0] = edge;
}

Square::Square():
Figure::Figure({0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0}, "black") {
	Area = 0;
	Diagonal = 0;
}

Square::Square(initializer_list<double> vertices, double edge, char* color): 
Figure::Figure(vertices, {edge, edge, edge, edge}, color) {
	Area = edge*edge;
	Diagonal = edge*sqrt(2);
}

double Square::GetArea() {
	Area = this->Edges[0]*this->Edges[0];
	return Area;
}

double Square::GetDiagonal() {
	Diagonal = this->Edges[0]*sqrt(2);
	return Diagonal;
}

Circle::Circle():
Figure::Figure({0, 0}, {0}, "black") {
	Radius = 0;
	Center[0] = 0;
	Center[1] = 0;
}

Circle::Circle(array<double, 2> center, double radius, char* color):
Figure::Figure({center[0], center[1]}, {radius}, color) {
	Radius = radius;
	Center[0] = center[0];
	Center[1] = center[1];
}

double Circle::GetArea() {
	double Area = Radius*Radius*3.14;
	return Area;
}

void Circle::PrintCircle() {
	cout << "Coordinates: " << Center[0] << " " << Center[1] << endl;
	cout << "Radius: " << Radius;
}

void operator>>(ifstream& ifs, Circle& c) {
	ifs >> c.Center[0] >> c.Center[1] >> c.Radius;
	c.SetValues({c.Center[0], c.Center[1]}, {c.Radius});
}

/*void operator>>(ifstream& ifs, Square& s) {

}*/