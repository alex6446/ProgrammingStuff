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

class Cube3D {
private:

	RenderWindow *window;
	vector<Vector3f> vertexBuffer;
	vector<Vector2i> indexBuffer;
	VertexArray line;
	Vector3f center;
	int size;
	float step;

public:

	Cube3D (RenderWindow *window) {
		this->window = window;
		setup();
	}

	void move (Sides side) {
		for (auto &i : vertexBuffer)
			i = move_position(i, side);
	}

	void update () {
		return;
	}

	void draw () {
		for (int i = 0; i < indexBuffer.size(); i++) {
			if (vertexBuffer[indexBuffer[i].x].z > 0 || 
				vertexBuffer[indexBuffer[i].y].z > 0) {
				line[0].position = convert_position(vertexBuffer[indexBuffer[i].x]);
				line[1].position = convert_position(vertexBuffer[indexBuffer[i].y]);
				window->draw(line);
			}
		}
	}

private:

	void setup () {
		step = 0.1;
		center = Vector3f(window->getSize().x/2, window->getSize().y/2, 0.f);
		size = min(window->getSize().x, window->getSize().y)/2;
		vertexBuffer = {Vector3f(-1, -1, -1), Vector3f(-1, -1, 1), 
						Vector3f(-1, 1, -1), Vector3f(-1, 1, 1), 
						Vector3f(1, -1, -1), Vector3f(1, -1, 1), 
						Vector3f(1, 1, -1), Vector3f(1, 1, 1)};
		indexBuffer = {Vector2i(0,1), Vector2i(1,3), Vector2i(2,3), 
					   Vector2i(2,0), Vector2i(4,5), Vector2i(4,6), 
					   Vector2i(6,7), Vector2i(7,5), Vector2i(0,4), 
					   Vector2i(1,5), Vector2i(2,6), Vector2i(3,7)};
		line.setPrimitiveType(LinesStrip);
		line.append(Vertex(Vector2f(0.f, 0.f)));
		line.append(Vertex(Vector2f(0.f, 0.f)));
	}

	Vector3f move_position (Vector3f position, Sides side) {
		switch (side) {
			case Sides::Right: 
				return Vector3f(position.x-step, position.y, position.z);
			case Sides::Left:
				return Vector3f(position.x+step, position.y, position.z);
			case Sides::Up:
				return Vector3f(position.x, position.y+step, position.z);
			case Sides::Down:
				return Vector3f(position.x, position.y-step, position.z);
			case Sides::Forward:
				return Vector3f(position.x, position.y, position.z-step);
			case Sides::Back:
				return Vector3f(position.x, position.y, position.z+step);
		}
		return position;
	}

	Vector2f convert_position (Vector3f position) {
		double k = 1;

		if (position.z > 0)
			k = size/position.z;
		else
			k = size*abs(position.z-2);
		return Vector2f(position.x * k + window->getSize().x/2, 
						position.y * k + window->getSize().y/2);

	}

};

int main() 
{
    RenderWindow window(VideoMode::getDesktopMode(), "Cube 2.0");
    window.setPosition(Vector2i(
	VideoMode::getDesktopMode().width/2 - window.getSize().x/2,
	VideoMode::getDesktopMode().height/2 - window.getSize().y/2));
	window.setFramerateLimit(60);

	Cube3D cube(&window);

    while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed)
				if (event.key.code == Keyboard::Escape)
					window.close();
			if (event.type == sf::Event::MouseWheelMoved)
				if (event.mouseWheel.delta > 0)
					cube.move(Sides::Forward);
				else 
					cube.move(Sides::Back);
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))
			cube.move(Sides::Right);
		else if (Keyboard::isKeyPressed(Keyboard::Left))
			cube.move(Sides::Left);
		if (Keyboard::isKeyPressed(Keyboard::Up))
			cube.move(Sides::Forward);
		else if (Keyboard::isKeyPressed(Keyboard::Down))
			cube.move(Sides::Back);
		if (Keyboard::isKeyPressed(Keyboard::Space))
			cube.move(Sides::Up);
		else if (Keyboard::isKeyPressed(Keyboard::RShift))
			cube.move(Sides::Down);

		cube.update();

		window.clear(Color(0,0,0));
		cube.draw();
		window.display();
	}
}
