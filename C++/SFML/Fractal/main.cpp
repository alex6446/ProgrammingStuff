#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

#define PI 3.14159265

enum class Sides {Right, Left, Up, Down};

class Fractal {
private:

	RenderWindow *window;
	int size;
	double scale;
	int step;
	int r;
	Vector2f center;
	CircleShape pattern;
	vector<CircleShape> triangle;
	vector<CircleShape> dots;

public:

	Fractal (RenderWindow *window, int size, int r = 2) {
		this->window = window;
		this->size = size;
		this->r = r;
		setup();
		generate();
	}

	void resize (int k) {
		for (auto &i : triangle)
			i.setPosition(resize_position(i.getPosition(), k));
		for (auto &i : dots)
			i.setPosition(resize_position(i.getPosition(), k));
	}

	void move (Sides side) {
		for (auto &i : triangle)
			i.setPosition(move_position(i.getPosition(), side));
		for (auto &i : dots)
			i.setPosition(move_position(i.getPosition(), side));
	}

	void draw () {
		for (auto &i : triangle)
			window->draw(i);
		for (auto &i : dots)
			window->draw(i);
	}

private:

	void setup () {
		center = Vector2f(window->getSize().x/2, window->getSize().y/2);
		pattern.setRadius(r);
		pattern.setOrigin(r,r);

		pattern.setPosition(Vector2f(center.x, center.y-center.y*0.5));
		triangle.push_back(pattern);
		pattern.setPosition(Vector2f(center.x-center.x*0.5, center.y-center.y*-0.5));
		triangle.push_back(pattern);
		pattern.setPosition(Vector2f(center.x-center.x*-0.5, center.y-center.y*-0.5));
		triangle.push_back(pattern);
		scale = 1.2;
		step = 5;
	}

	void generate () {
		pattern.setPosition(triangle[0].getPosition()+triangle[1].getPosition());
		pattern.setPosition(pattern.getPosition().x/2, pattern.getPosition().y/2);
		dots.push_back(pattern);
		srand(time(NULL));
		for (int i = 0; i < size; i++) {
			pattern.setPosition(dots.back().getPosition() + triangle[rand()%3].getPosition());
			pattern.setPosition(pattern.getPosition().x/2, pattern.getPosition().y/2);
			dots.push_back(pattern);
		}
	}

	Vector2f move_position (Vector2f position, Sides side) {
		switch (side) {
			case Sides::Right: 
				return Vector2f(position.x-step, position.y);
			case Sides::Left:
				return Vector2f(position.x+step, position.y);
			case Sides::Up:
				return Vector2f(position.x, position.y+step);
			case Sides::Down:
				return Vector2f(position.x, position.y-step);
		}
		return position;
	}

	Vector2f resize_position (Vector2f position, int k) {
		Vector2f sides = position - center;
		float angle;
		if (sides.x) angle = atan2(sides.y, sides.x);
		else if (center.y > sides.y) angle = -PI/2;
		else angle = PI/2;

		float length;
		if (k > 0) 
			length = sqrt(pow(sides.x, 2) + pow(sides.y, 2))*scale;
		else
			length = sqrt(pow(sides.x, 2) + pow(sides.y, 2))/scale;

		return Vector2f(center.x + cos(angle)*length, 
						center.y + sin(angle)*length);
	}

};

int main() 
{
    RenderWindow window(VideoMode(800, 600), "Fractal");
    window.setPosition(Vector2i(
	VideoMode::getDesktopMode().width/2 - window.getSize().x/2,
	VideoMode::getDesktopMode().height/2 - window.getSize().y/2));
	window.setFramerateLimit(60);

	Fractal fractal(&window, 200000, 1);

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
					fractal.move(Sides::Up);
				else fractal.move(Sides::Down);
		}

		if (Keyboard::isKeyPressed(Keyboard::Right))
			fractal.move(Sides::Right);
		else if (Keyboard::isKeyPressed(Keyboard::Left))
			fractal.move(Sides::Left);
		if (Keyboard::isKeyPressed(Keyboard::Up))
			fractal.resize(1);
		else if (Keyboard::isKeyPressed(Keyboard::Down))
			fractal.resize(-1);

		window.clear(Color(0,0,0));
		fractal.draw();
		window.display();
	}
}

