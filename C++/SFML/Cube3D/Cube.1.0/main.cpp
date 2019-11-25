#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
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
	vector<CircleShape> verticies;
	CircleShape top;
	Vector3f center;
	int step;

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
		for (int i = 0; i < vertexBuffer.size(); i++) {
			verticies[i].setPosition(convert_position(vertexBuffer[i]));
			cout << vertexBuffer[i].x << " " << vertexBuffer[i].y << " " 
				 << vertexBuffer[i].z; 
			cout << '\t' << verticies[i].getPosition().x << " " 
				 << verticies[i].getPosition().y << endl; 
		}
	}

	void draw () {
		for (auto &i : verticies)
			window->draw(i);
	}

private:

	void setup () {
		center = Vector3f(window->getSize().x/2, window->getSize().y/2, 0.f);
		step = 1;
		vertexBuffer = {Vector3f(-1,-1,2), Vector3f(1,-1,2), 
						Vector3f(1,1,2),   Vector3f(-1,1,2), 
						Vector3f(-1,-1,16),  Vector3f(1,-1,16), 
						Vector3f(1,1,16),    Vector3f(-1,1,16)};
		indexBuffer = {Vector2i(0,1), Vector2i(1,2), Vector2i(2,3), 
					   Vector2i(3,0), Vector2i(4,5), Vector2i(5,6), 
					   Vector2i(6,7), Vector2i(7,4), Vector2i(0,4), 
					   Vector2i(1,5), Vector2i(2,6), Vector2i(3,7)};
		top.setRadius(2);
		top.setOrigin(2, 2);
		for (int i = 0; i < vertexBuffer.size(); i++)
			verticies.push_back(top);
	}

	Vector3f move_position (Vector3f position, Sides side) {
		float k = step - position.z/step*0.2;
		switch (side) {
			case Sides::Right: 
				return Vector3f(position.x-(step - (position.z+25)/step*0.00001), position.y, position.z);
			case Sides::Left:
				return Vector3f(position.x+(step - (position.z+25)/step*0.00001), position.y, position.z);
			case Sides::Up:
				return Vector3f(position.x, position.y+k, position.z);
			case Sides::Down:
				return Vector3f(position.x, position.y-k, position.z);
			case Sides::Forward:
				return Vector3f(position.x, position.y, position.z-(step - (position.z+25)/step*0.2));
			case Sides::Back:
				return Vector3f(position.x, position.y, position.z+(step - (position.z+25)/step*0.2));
		}
		return position;
	}

	Vector2f convert_position (Vector3f position) {
		Vector3f sides = position;
		float angle;
		if (sides.x) angle = atan2(sides.y, sides.x);
		else if (center.y > sides.y) angle = -PI/2;
		else angle = PI/2;

		float length;
		length = sqrt(pow(sides.x, 2) + pow(sides.y, 2))*position.z;
		//length = sqrt(pow(sides.x, 2) + pow(sides.y, 2))/position.z;

		return Vector2f(center.x + cos(angle)*length, 
						center.y + sin(angle)*length);
	}

};

int main() 
{
    RenderWindow window(VideoMode::getDesktopMode(), "Fractal");
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
				/*if (event.key.code == Keyboard::Right)
					cube.move(Sides::Right);
				if (event.key.code == Keyboard::Left)
					cube.move(Sides::Left);
				if (event.key.code == Keyboard::Up)
					cube.move(Sides::Forward);
				if (event.key.code == Keyboard::Down)
					cube.move(Sides::Back);*/
		}

		if (Keyboard::isKeyPressed(Keyboard::Right))
			cube.move(Sides::Right);
		else if (Keyboard::isKeyPressed(Keyboard::Left))
			cube.move(Sides::Left);
		if (Keyboard::isKeyPressed(Keyboard::Up))
			cube.move(Sides::Forward);
		else if (Keyboard::isKeyPressed(Keyboard::Down))
			cube.move(Sides::Back);

		cube.update();

		window.clear(Color(0,0,0));
		cube.draw();
		window.display();
	}
}


