#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <SFML/Graphics.hpp>

#include "Cube3D.h"

using namespace std;
using namespace sf;

Cube3D::Cube3D () {
	setup();
}

Cube3D::Cube3D (Vector3f position, float size) {
	setup();
	setPosition(position);
	setSize(size);
}

void Cube3D::setup () {
	vertexBuffer = {
					Vector3f(-1, -1, -1), Vector3f(1, 1, 1),   // 0 1
					Vector3f(-1, 1, 1),   Vector3f(1, -1, -1), // 2 3
					Vector3f(1, -1, 1),   Vector3f(-1, 1, -1), // 4 5
					Vector3f(1, 1, -1),   Vector3f(-1, -1, 1)  // 6 7
				   };
	indexBuffer  = {
					Vector3i(0,6,5), Vector3i(0,6,3), // Front
					Vector3i(7,1,2), Vector3i(7,1,4), // Back
					Vector3i(1,5,6), Vector3i(1,5,2), // Up
					Vector3i(0,4,7), Vector3i(0,4,3), // Down
					Vector3i(1,3,6), Vector3i(1,3,4), // Right
					Vector3i(0,2,7), Vector3i(0,2,5)  // Left
				   };
	colorBuffer  = {
					Color(0, 155, 72),     Color(0, 155, 72),
					Color(0, 69, 173),     Color(0, 69, 173),
					Color(255, 2555, 255), Color(255, 255, 255),
					Color(255, 213, 0),    Color(255, 213, 0),
					Color(255, 89, 0),     Color(255, 89, 0),
					Color(185, 0, 0),      Color(185, 0, 0) 
				   };
}
