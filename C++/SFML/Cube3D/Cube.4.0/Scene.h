#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <SFML/Graphics.hpp>

#include "Object3D.h"
#include "Camera.h"

using namespace std;
using namespace sf;

class Scene {
private:

	RenderWindow *window;
	vector<Object3D *> objects;
	vector<Camera *> cameras;
	Camera *camera;

public:

	Scene (RenderWindow &window);

	void addCamera (Camera *camera);
	void setCamera (int i);

	void addObject (Object3D *object);

	void update ();

	void draw ();

};