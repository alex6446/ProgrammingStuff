#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

enum class Sides {Right, Left, Up, Down, Forward, Back};

class Camera {
private:

	Vector3f position;
	Vector3f rotation;
	float step;

public:

	Camera ();
	Camera (Vector3f position, float step=1.f, Vector3f rotation = Vector3f(0.f, 0.f, 0.f));

	void move (Sides side);
	void rotate (Vector3f angle);

	Vector3f getRotation ();
	void setRotation (Vector3f rotation);

	Vector3f getPosition ();
	void setPosition (Vector3f position);

	float getStep ();
	void setStep (float step);

};