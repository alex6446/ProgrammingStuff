#pragma once

#include "Object3D.h"

class Cube3D : public Object3D {
public:

	Cube3D ();
	Cube3D (Vector3f position, float size=1.f);

private:

	void setup ();
};