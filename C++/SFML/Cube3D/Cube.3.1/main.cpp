#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

#define PI 3.14159265
enum class Sides {Right, Left, Up, Down, Forward, Back};


class Camera {
private:

	Vector3f position;
	Vector2f rotation;
	float step;

public:

	Camera () {
		this->position = Vector3f(0.f, 0.f, -5.f);
		this->rotation = Vector2f(0.f, 0.f);
		step = 1.f;
	}

	Camera (Vector3f position, float step=1.f, Vector2f rotation = Vector2f(0.f, 0.f)) {
		this->position = position;
		this->rotation = rotation;
		this->step = step;
	}

	void move (Sides side) {
		switch (side) {
			case Sides::Right: 
				position = Vector3f(position.x+step*cos(rotation.x*0.0175), position.y, 
									position.z-step*sin(rotation.x*0.0175));break;
			case Sides::Left:
				position = Vector3f(position.x-step*cos(rotation.x*0.0175), position.y, 
									position.z+step*sin(rotation.x*0.0175));break;
			case Sides::Up:
				position = Vector3f(position.x, position.y-step, position.z);break;
			case Sides::Down:
				position = Vector3f(position.x, position.y+step, position.z);break;
			case Sides::Forward:
				position = Vector3f(position.x+step*sin(rotation.x*0.0175), position.y, 
									position.z+step*cos(rotation.x*0.0175));break;
			case Sides::Back:
				position = Vector3f(position.x-step*sin(rotation.x*0.0175), position.y, 
									position.z-step*cos(rotation.x*0.0175));
		}
	}

	void rotate (Vector2f angle) { setRotation(rotation + angle); }

	Vector2f getRotation () { return rotation; }
	void setRotation (Vector2f rotation) {
		this->rotation = rotation;
		if (rotation.x > 360.f)
			rotation -= Vector2f(360.f, 0.f);
		if (rotation.y > 360.f)
			rotation -= Vector2f(0.f, 360.f);
	}

	Vector3f getPosition () { return position; }
	void setPosition (Vector3f position) {
		this->position = position;
	}

	float getStep () { return step; }
	void setStep (float step) { this->step = step; }

};

class Object3D {
protected:
	
	vector<Vector3f> vertexBuffer;
	vector<Vector2i> indexBuffer;
	Vector3f position;
	Vector2f rotation;
	RenderWindow *window;
	Vector2f center;
	float size;

private:

	VertexArray line;
	float screen;

public:

	Object3D () {
		setup();
	}

	Vector3f getPosition () { return position; }
	void setPosition (Vector3f position) { updatePosition(position); }

	float getSize () { return size; }
	void setSize (float size) { updateSize(size); }

	void setWindow (RenderWindow &window) { adjust(window); }

	void rotate (Vector2f angle) { setRotation(rotation + angle); }

	Vector2f getRotation () { return rotation; }
	void setRotation (Vector2f rotation) {
		this->rotation = rotation;
		if (rotation.x > 360.f)
			rotation -= Vector2f(360.f, 0.f);
		if (rotation.y > 360.f)
			rotation -= Vector2f(0.f, 360.f);
	}

	void draw (Camera *camera) {
		for (int i = 0; i < indexBuffer.size(); i++) {
			Vector3f transformed[2] = {
				convert_rotation(vertexBuffer[indexBuffer[i].x], camera->getPosition(), 
										camera->getRotation()) - camera->getPosition(),
				convert_rotation(vertexBuffer[indexBuffer[i].y], camera->getPosition(), 
										camera->getRotation()) - camera->getPosition()
			};
			if (transformed[0].z > 0 && transformed[1].z > 0) {
				line[0].position = convert_position(transformed[0])+center;
				line[1].position = convert_position(transformed[1])+center;
				window->draw(line);
			} else if (transformed[0].z > 0) {
				line[0].position = convert_position(transformed[0])+center;
				line[1].position = convert_position(clip_z(transformed))+center;
				window->draw(line);
			} else if (transformed[1].z > 0) {
				line[0].position = convert_position(clip_z(transformed))+center;
				line[1].position = convert_position(transformed[1])+center;
				window->draw(line);
			}
		}
	}

private:

	void setup () {
		line.setPrimitiveType(LinesStrip);
		line.append(Vertex(Vector2f(0.f, 0.f)));
		line.append(Vertex(Vector2f(0.f, 0.f)));
		size = 1.f;
		position = Vector3f(0.f, 0.f, 0.f);
	}

	Vector2f convert_position (Vector3f position) {
		double k = screen/position.z;
		return Vector2f(position.x * k, position.y * k);
	}

	Vector3f convert_rotation (Vector3f position, Vector3f point, Vector2f angle) {
		float fi_x = angle.x*0.0175;
		float fi_y = angle.y*0.0175;
		Vector3f result = position - point;
		result = Vector3f(
			result.x*cos(fi_x) - result.z*sin(fi_x),
			result.y,
			result.x*sin(fi_x) + result.z*cos(fi_x)
		);
		result = Vector3f(
			result.x,
			result.y*cos(fi_y) - result.z*sin(fi_y),
			result.y*sin(fi_y) + result.z*cos(fi_y)
		);
		return result+point;
	}

	Vector3f clip_z (Vector3f point[]) {
		float near = 0.00001;
		float k = (near - point[0].z) / (point[1].z - point[0].z);
		return Vector3f(k * (point[1].x - point[0].x) + point[0].x,
						k * (point[1].y - point[0].y) + point[0].y,
						near);
	}

	void adjust (RenderWindow &window) {
		this->window = &window;
		center = Vector2f(window.getSize())/2.f;
		screen = min(center.x, center.y);
		//screen = window.getSize().y;
	}

	void updatePosition (Vector3f position) {
		for (auto &i : vertexBuffer)
			i = i - this->position + position;
		this->position = position;
	}

	void updateSize (float size) {
		for (auto &i : vertexBuffer)
			i = (i-position)/this->size*size+position;
		this->size = size;
	}

};



class Cube3D : public Object3D {
public:

	Cube3D () {
		setup();
	}

	Cube3D (Vector3f position, float size=1.f) {
		setup();
		setPosition(position);
		setSize(size);
	}

private:

	void setup () {
		vertexBuffer = {Vector3f(-1, -1, -1), Vector3f(-1, -1, 1), 
						Vector3f(-1, 1, -1), Vector3f(-1, 1, 1), 
						Vector3f(1, -1, -1), Vector3f(1, -1, 1), 
						Vector3f(1, 1, -1), Vector3f(1, 1, 1)};
		indexBuffer = {Vector2i(0,1), Vector2i(1,3), Vector2i(2,3), 
					   Vector2i(2,0), Vector2i(4,5), Vector2i(4,6), 
					   Vector2i(6,7), Vector2i(7,5), Vector2i(0,4), 
					   Vector2i(1,5), Vector2i(2,6), Vector2i(3,7)};
	}
};

class Scene {
private:

	RenderWindow *window;
	vector<Object3D *> objects;
	vector<Camera *> cameras;
	Camera *camera;

public:

	Scene (RenderWindow &window) {
		this->window = &window;
	}

	void addCamera (Camera *camera) { cameras.push_back(camera); }
	void setCamera (int i) { camera = cameras[i]; }

	void addObject (Object3D *object) {
		object->setWindow(*window);
		objects.push_back(object);
	}

	void update () {
		if (Keyboard::isKeyPressed(Keyboard::D))
			camera->move(Sides::Right);
		else if (Keyboard::isKeyPressed(Keyboard::A))
			camera->move(Sides::Left);
		if (Keyboard::isKeyPressed(Keyboard::W))
			camera->move(Sides::Forward);
		else if (Keyboard::isKeyPressed(Keyboard::S))
			camera->move(Sides::Back);
		if (Keyboard::isKeyPressed(Keyboard::Space))
			camera->move(Sides::Up);
		else if (Keyboard::isKeyPressed(Keyboard::LShift))
			camera->move(Sides::Down);
		if (Keyboard::isKeyPressed(Keyboard::Q))
			cout << camera->getPosition().x << ", " 
				 << camera->getPosition().y << ", " << camera->getPosition().z << endl;
		camera->rotate((Vector2f(Mouse::getPosition(*window))- Vector2f(window->getSize())*0.5f)*0.1f);
		Mouse::setPosition(Vector2i(Vector2f(window->getSize())*0.5f), *window);
	}

	void draw () {
		for (auto i : objects) 
			i->draw(camera);
	}

};

int main() 
{
    RenderWindow window(VideoMode::getDesktopMode(), "Cube 3.0");
    window.setPosition(Vector2i(
	VideoMode::getDesktopMode().width/2 - window.getSize().x/2,
	VideoMode::getDesktopMode().height/2 - window.getSize().y/2));
	window.setFramerateLimit(60);
	window.setMouseCursorVisible(false);

	Scene scene(window);
	scene.addCamera(new Camera(Vector3f(0.f, 0.f, 0.f), 0.1f));
	scene.addCamera(new Camera(Vector3f(0.976187, 2, 0.72065)));
	scene.addObject(new Cube3D());
/*	scene.addObject(new Cube3D(Vector3f(-120.f, 0.f, 40.f), 20));
	scene.addObject(new Cube3D(Vector3f(-120.f, 0.f, 80.f), 20));
	scene.addObject(new Cube3D(Vector3f(-60.f, 0.f, 40.f), 20));
	scene.addObject(new Cube3D(Vector3f(-60.f, 0.f, 80.f), 20));*/
	scene.addObject(new Cube3D(Vector3f(3.f, 0.f, 0.f)));
	scene.addObject(new Cube3D(Vector3f(-3.f, 0.f, 0.f)));
	scene.addObject(new Cube3D(Vector3f(0.f, 3.f, 0.f)));
	scene.addObject(new Cube3D(Vector3f(0.f, -3.f, 0.f)));
	scene.addObject(new Cube3D(Vector3f(0.f, 0.f, 3.f)));
	scene.addObject(new Cube3D(Vector3f(0.f, 0.f, -3.f)));

	scene.addObject(new Cube3D(Vector3f(6.f, 0.f, 0.f)));
	scene.addObject(new Cube3D(Vector3f(6.f, 2.f, 0.f)));
	scene.addObject(new Cube3D(Vector3f(8.f, 2.f, 0.f)));
	scene.addObject(new Cube3D(Vector3f(8.f, 0.f, 0.f)));

	scene.setCamera(0);

    while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed)
				if (event.key.code == Keyboard::Escape)
					window.close();
		}
		
		scene.update();

		window.clear(Color(0,0,0));
		scene.draw();
		window.display();
	}
}
