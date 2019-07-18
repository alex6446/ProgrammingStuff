#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

int main() 
{
	RenderWindow window(VideoMode(640, 400), "Gravity Ball");
	window.setFramerateLimit(60);

	CircleShape shape(10.f);
    shape.setFillColor(Color::Green);
    shape.setPosition(Vector2f(300.f, 20.f));

    float V = 0.f;
    float a = 9.82;
    float y = shape.getPosition().y;
    float dt = 0.4; // change only this

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}

		/////////// UPDATE /////////////////////////////////////////////

		if (shape.getPosition().y + shape.getRadius()*2 >= 400 && V > 0) {
			V *= -1;
			dt += 0.1;
		}

		V = V + a*dt;
		y = y + V*dt;

		if (Keyboard::isKeyPressed(Keyboard::Right))
			shape.setPosition(Vector2f(shape.getPosition().x + 3.f, y));
		else if (Keyboard::isKeyPressed(Keyboard::Left)) {
			shape.setPosition(Vector2f(shape.getPosition().x - 3.f, y));
		} else if (Keyboard::isKeyPressed(Keyboard::Down)) {
			V = 0.f;
		    a = 9.82;
		    y = 20.f;
		    dt = 0.4;
		} else
			shape.setPosition(Vector2f(shape.getPosition().x, y));

		if (y + shape.getRadius()*2 > 400)
			shape.setPosition(Vector2f(shape.getPosition().x, 400 - shape.getRadius()*2));

		/////////// DRAW ///////////////////////////////////////////////

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}
