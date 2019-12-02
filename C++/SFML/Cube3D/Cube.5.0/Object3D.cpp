#include "Object3D.h"

Object3D::Object3D () {
	setup();
}

Vector3f Object3D::getPosition () { return position; }
void Object3D::setPosition (Vector3f position) { updatePosition(position); }

void Object3D::move (Vector3f direction) { setPosition(position + direction); }

float Object3D::getSize () { return size; }
void Object3D::setSize (float size) { updateSize(size); }

void Object3D::setWindow (RenderWindow &window) { adjust(window); }

Vector3f Object3D::getRotation () { return rotation; }
void Object3D::setRotation (Vector3f rotation) { updateRotation(rotation); }

void Object3D::rotate (Vector3f angle) { setRotation(rotation + angle); }
void Object3D::rotate (Vector3f angle, Vector3f point) {
	for (auto &i : vertexBuffer)
		i = convert_rotation(i, point, angle);
	position = convert_rotation(position, point, angle);
}

void Object3D::draw (Camera *camera) {
	for (int i = 0; i < indexBuffer.size(); i++) {
		line.clear();
		polygon.clear();
		Color color = colorBuffer[i%colorBuffer.size()];
		Vector3f transformed[3] = {
			convert_rotation(vertexBuffer[indexBuffer[i].x], camera->getPosition(), 
									camera->getRotation()) - camera->getPosition(),
			convert_rotation(vertexBuffer[indexBuffer[i].y], camera->getPosition(), 
									camera->getRotation()) - camera->getPosition(),
			convert_rotation(vertexBuffer[indexBuffer[i].z], camera->getPosition(), 
									camera->getRotation()) - camera->getPosition()
		};
		if (transformed[0].z > 0 && transformed[1].z > 0 && transformed[2].z > 0) {
			line.append(convert_position(transformed[0])+center);
			line.append(convert_position(transformed[1])+center);
			line.append(convert_position(transformed[2])+center);
			line.append(convert_position(transformed[0])+center);
			window->draw(line);
			polygon.append(Vertex(convert_position(transformed[0])+center, color));
			polygon.append(Vertex(convert_position(transformed[1])+center, color));
			polygon.append(Vertex(convert_position(transformed[2])+center, color));
			//window->draw(polygon);
		}
	}
}

void Object3D::setup () {
	line.setPrimitiveType(LinesStrip);
	polygon.setPrimitiveType(TriangleStrip);
	size = 1.f;
	position = Vector3f(0.f, 0.f, 0.f);
}

Vector2f Object3D::convert_position (Vector3f position) {
	double k = screen/position.z;
	return Vector2f(position.x * k, position.y * k);
}

Vector3f Object3D::convert_rotation (Vector3f position, Vector3f point, Vector3f angle) {
	float fi_x = angle.x*0.0175;
	float fi_y = angle.y*0.0175;
	float fi_z = angle.z*0.0175;
	Vector3f result = position - point;
	result = Vector3f(
		result.x*cos(fi_y) - result.z*sin(fi_y),
		result.y,
		result.x*sin(fi_y) + result.z*cos(fi_y)
	);
	result = Vector3f(
		result.x,
		result.y*cos(fi_x) - result.z*sin(fi_x),
		result.y*sin(fi_x) + result.z*cos(fi_x)
	);
	result = Vector3f(
		result.x*cos(fi_z) - result.y*sin(fi_z),
		result.x*sin(fi_z) + result.y*cos(fi_z),
		result.z
	);
	return result+point;
}

Vector3f Object3D::clip_z (Vector3f point[]) {
	float near = 0.00001;
	float k = (near - point[0].z) / (point[1].z - point[0].z);
	return Vector3f(k * (point[1].x - point[0].x) + point[0].x,
					k * (point[1].y - point[0].y) + point[0].y,
					near);
}

void Object3D::adjust (RenderWindow &window) {
	this->window = &window;
	center = Vector2f(window.getSize())/2.f;
	screen = min(center.x, center.y);
	//screen = window.getSize().y;
}

void Object3D::updatePosition (Vector3f position) {
	for (auto &i : vertexBuffer)
		i = i - this->position + position;
	this->position = position;
}

void Object3D::updateSize (float size) {
	for (auto &i : vertexBuffer)
		i = (i-position)/this->size*size+position;
	this->size = size;
}

void Object3D::updateRotation (Vector3f rotation) {
	for (auto &i : vertexBuffer)
		i = convert_rotation(i, position, rotation - this->rotation);
	this->rotation = rotation;
	if (rotation.x > 360.f)
		rotation -= Vector3f(360.f, 0.f, 0.f);
	if (rotation.y > 360.f)
		rotation -= Vector3f(0.f, 360.f, 0.f);
	if (rotation.z > 360.f)
		rotation -= Vector3f(0.f, 0.f, 360.f);
}
