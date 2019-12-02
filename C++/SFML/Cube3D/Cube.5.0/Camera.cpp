#include "Camera.h"

Camera::Camera () {
	this->position = Vector3f(0.f, 0.f, -5.f);
	this->rotation = Vector3f(0.f, 0.f, 0.f);
	step = 1.f;
}

Camera::Camera (Vector3f position, float step, Vector3f rotation) {
	this->position = position;
	this->rotation = rotation;
	this->step = step;
}

void Camera::move (Sides side) {
	switch (side) {
		case Sides::Right: 
			position = Vector3f(position.x+step*cos(rotation.y*0.0175), position.y, 
								position.z-step*sin(rotation.y*0.0175));break;
		case Sides::Left:
			position = Vector3f(position.x-step*cos(rotation.y*0.0175), position.y, 
								position.z+step*sin(rotation.y*0.0175));break;
		case Sides::Up:
			position = Vector3f(position.x, position.y-step, position.z);break;
		case Sides::Down:
			position = Vector3f(position.x, position.y+step, position.z);break;
		case Sides::Forward:
			position = Vector3f(position.x+step*sin(rotation.y*0.0175), position.y, 
								position.z+step*cos(rotation.y*0.0175));break;
		case Sides::Back:
			position = Vector3f(position.x-step*sin(rotation.y*0.0175), position.y, 
								position.z-step*cos(rotation.y*0.0175));
	}
}

void Camera::rotate (Vector3f angle) { setRotation(rotation + angle); }

Vector3f Camera::getRotation () { return rotation; }
void Camera::Camera::setRotation (Vector3f rotation) {
	this->rotation = rotation;
	if (rotation.x > 360.f)
		rotation -= Vector3f(360.f, 0.f, 0.f);
	if (rotation.y > 360.f)
		rotation -= Vector3f(0.f, 360.f, 0.f);
	if (rotation.z > 360.f)
		rotation -= Vector3f(0.f, 0.f, 360.f);
}

Vector3f Camera::getPosition () { return position; }
void Camera::setPosition (Vector3f position) {
	this->position = position;
}

float Camera::getStep () { return step; }
void Camera::setStep (float step) { this->step = step; }





