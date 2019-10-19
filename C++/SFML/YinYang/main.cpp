#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

#define PI 3.14159265

int main()
{
    RenderWindow window(VideoMode(800, 520), "Yin Yang");
    window.setPosition(Vector2i(
	VideoMode::getDesktopMode().width/2 - window.getSize().x/2,
	VideoMode::getDesktopMode().height/2 - window.getSize().y/2));
	window.setFramerateLimit(60);

	float r = 100;
	float R = 2*r;
	double l = -0.6;
    double fi = 180*l/PI/r;
    double fir = fi*0.0175;
	Vector2f center = Vector2f(window.getSize().x/2, window.getSize().y/2);
    Vector2f position1 = Vector2f(center.x + r, center.y);
    Vector2f position2 = Vector2f(center.x - r, center.y);

    Texture MainBallTex;
    MainBallTex.loadFromFile("whiteblack.jpg");
    CircleShape MainBall(R, 60);
    MainBall.setOrigin(Vector2f(R, R));
    MainBall.setTexture(&MainBallTex);
    MainBall.setPosition(center);
    MainBall.setRotation(-90);

    Texture ballTex;
    ballTex.loadFromFile("yinyang.jpg");
    CircleShape ball1(r, 60);
    ball1.setOrigin(Vector2f(r, r));
    ball1.setTexture(&ballTex);
    ball1.setPosition(position1);
    ball1.setRotation(-90);

    CircleShape ball2(r, 60);
    ball2.setOrigin(Vector2f(r, r));
    ball2.setTexture(&ballTex);
    ball2.setPosition(position2);
    ball2.setRotation(-90);

    while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed)
				if (event.key.code == Keyboard::Escape)
					window.close();
		}
		position1 = ball1.getPosition() - center;
		position2 = ball2.getPosition() - center;
		ball1.setPosition(Vector2f(
			position1.x*cos(fir) - position1.y*sin(fir),
			position1.x*sin(fir) + position1.y*cos(fir)
		) + center);
		ball1.rotate(-fi);
		ball2.setPosition(Vector2f(
			position2.x*cos(fir) - position2.y*sin(fir),
			position2.x*sin(fir) + position2.y*cos(fir)
		) + center);
		ball2.rotate(-fi);

		MainBall.rotate(fi);

		window.clear(Color(0,128,128));
		window.draw(MainBall);
		window.draw(ball1);
		window.draw(ball2);
		window.display();
	}
}
