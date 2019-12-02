#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <SFML/Graphics.hpp>

#include "Camera.h"

using namespace std;
using namespace sf;

class Object3D {
protected:
	
	vector<Vector3f> vertexBuffer;
	vector<Vector3i> indexBuffer;
	vector<Color> colorBuffer;
	Vector3f position;
	Vector3f rotation;
	RenderWindow *window;
	Vector2f center;
	float size;

private:

	VertexArray line;
	VertexArray polygon;
	float screen;

public:

	Object3D ();

	Vector3f getPosition ();
	void setPosition (Vector3f position);
	void move (Vector3f direction);

	float getSize ();
	void setSize (float size);

	void setWindow (RenderWindow &window);

	Vector3f getRotation ();
	void setRotation (Vector3f rotation);
	void rotate (Vector3f angle);
	void rotate (Vector3f angle, Vector3f point);

	void draw (Camera *camera);

private:

	void setup ();

	Vector2f convert_position (Vector3f position);
	Vector3f convert_rotation (Vector3f position, Vector3f point, Vector3f angle);

	Vector3f clip_z (Vector3f point[]);

	void adjust (RenderWindow &window);

	void updatePosition (Vector3f position);
	void updateRotation (Vector3f rotation);
	void updateSize (float size);

};