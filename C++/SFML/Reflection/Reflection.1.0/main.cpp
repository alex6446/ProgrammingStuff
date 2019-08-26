#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

#define PI 3.14159265

using namespace sf;

int main () 
{
	// Window
	RenderWindow window(VideoMode(640, 450), "Reflection 1.0");
	window.setFramerateLimit(60);

	// Sprites
	Texture torchTex;
	Sprite torch;

	torchTex.loadFromFile("Torch.png");
	torch.setTexture(torchTex);
	torch.setScale(Vector2f(0.1f, 0.1f));
	torch.setOrigin(Vector2f(torch.getLocalBounds().width / 2, 
							 torch.getLocalBounds().height / 2));
	torch.setPosition(Vector2f(window.getSize().x / 2, window.getSize().y / 2));
	torch.setRotation(135.f);

	Font font;
	font.loadFromFile("Roboto-Regular.ttf");

	Text console;
	console.setFont(font);
	console.setCharacterSize(24);

	Vertex light[] = { Vertex(torch.getPosition(), Color::Yellow), Vertex(Vector2f(600.f, 400.f), Color::Yellow) };
	Vertex reflection[] = { Vertex(light[1].position, Color::Yellow), Vertex(Vector2f(0.f, 0.f), Color::Yellow) };

	// Main loop
	while (window.isOpen()) {

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Escape)
					window.close();
			}
		}

		////////// UPDATE //////////////////////////////////////
		
		light[0] = Vertex(torch.getPosition(), Color::Yellow);

		Vector2f sides = Vector2f(torch.getPosition()) - 
						 Vector2f(Mouse::getPosition(window));
		float angleTorch = atan2(sides.y, sides.x) * 180 / PI * -1 + 180;
		torch.setRotation(angleTorch * -1 + 135);

		//std::cout << angleTorch << std::endl;

		float angleWindow = atan2(window.getSize().y, window.getSize().x) * 180 / PI;

		/*console.setString(std::to_string(angleWindow));*/
		/*console.setString(std::to_string(180 - angleWindow));*/
		/*console.setString(std::to_string(angleWindow + 180));*/
		/*console.setString(std::to_string(360 - angleWindow));*/
		float x, y;
		float step;
		float angleReflection;
		float reflection_x, reflection_y;
		if (angleTorch <= angleWindow  || angleTorch >= 360 - angleWindow) {
			console.setString("1");
			x = window.getSize().x;
			y = tan(angleTorch * PI / 180 * -1) * x / 2 + window.getSize().y / 2;

			step = window.getSize().y / 3;
			if (y <= step) {
				angleReflection = atan2(light[0].position.x, 
										light[0].position.y - 
										light[1].position.y) * 180 / PI;
				console.setString(std::to_string(angleReflection));
				reflection_x = light[1].position.y * tan(angleReflection * PI / 180);
				reflection_y = 0;
				reflection_x = window.getSize().x - reflection_x;
			} else if (y <= window.getSize().y / 2) {
				angleReflection = atan2(light[0].position.x, 
										light[0].position.y - 
										light[1].position.y) * 180 / PI;
				console.setString(std::to_string(angleReflection));
				reflection_x = 0;
				reflection_y = light[0].position.y - window.getSize().x / tan(angleReflection * PI / 180) * 1.5;
			} else if (y <= step * 2) {
				angleReflection = atan2(light[0].position.x, 
										light[1].position.y - 
										light[0].position.y) * 180 / PI;
				console.setString(std::to_string(angleReflection));
				reflection_x = 0;
				reflection_y = light[0].position.y - window.getSize().x / tan(angleReflection * PI / 180) * 1.5;
				reflection_y = window.getSize().y - reflection_y;
			} else {
				angleReflection = atan2(light[0].position.x, 
										light[1].position.y - 
										light[0].position.y) * 180 / PI;
				console.setString(std::to_string(angleReflection));
				reflection_x = (window.getSize().y - light[1].position.y) * tan(angleReflection * PI / 180);
				reflection_y = window.getSize().y;
				reflection_x = window.getSize().x - reflection_x;
			}
		} else if (angleTorch <= 180 - angleWindow) {
			console.setString("2");
			y = 0;
			x = window.getSize().y / 2 / tan(angleTorch * PI / 180) + window.getSize().x / 2;
		
			step = window.getSize().x / 3;
			if (x <= step) {
				angleReflection = atan2(light[0].position.y, 
										light[0].position.x - 
										light[1].position.x) * 180 / PI;
				console.setString(std::to_string(angleReflection));
				reflection_x = 0;
				reflection_y = light[1].position.x * tan(angleReflection * PI / 180);
			} else if (x <= window.getSize().x / 2) {
				angleReflection = atan2(light[0].position.y, 
										light[0].position.x - 
										light[1].position.x) * 180 / PI;
				console.setString(std::to_string(angleReflection));
				reflection_x = light[0].position.x - window.getSize().y / tan(angleReflection * PI / 180) * 1.5;
				reflection_y = window.getSize().y;
			} else if (x <= step * 2) {
				angleReflection = atan2(light[0].position.y, 
										light[1].position.x - 
										light[0].position.x) * 180 / PI;
				console.setString(std::to_string(angleReflection));
				reflection_x = light[0].position.x - window.getSize().y / tan(angleReflection * PI / 180) * 1.5;
				reflection_y = window.getSize().y;
				reflection_x = window.getSize().x - reflection_x;
			} else {
				angleReflection = atan2(light[0].position.y, 
										light[1].position.x - 
										light[0].position.x) * 180 / PI;
				console.setString(std::to_string(angleReflection));
				reflection_x = window.getSize().x;
				reflection_y = (reflection_x - light[1].position.x) * tan(angleReflection * PI / 180);
			}
		} else if (angleTorch <= angleWindow + 180) {
			console.setString("3");
			x = 0;
			y = tan(angleTorch * PI / 180) * window.getSize().x / 2 + window.getSize().y / 2;
		
			step = window.getSize().y / 3;
			if (y <= step) {
				angleReflection = atan2(light[0].position.x, 
										light[0].position.y - 
										light[1].position.y) * 180 / PI;
				console.setString(std::to_string(angleReflection));
				reflection_x = light[1].position.y * tan(angleReflection * PI / 180);
				reflection_y = 0;
			} else if (y <= window.getSize().y / 2) {
				angleReflection = atan2(light[0].position.x, 
										light[0].position.y - 
										light[1].position.y) * 180 / PI;
				console.setString(std::to_string(angleReflection));
				reflection_x = window.getSize().x;
				reflection_y = light[0].position.y - window.getSize().x / tan(angleReflection * PI / 180) * 1.5;
			} else if (y <= step * 2) {
				angleReflection = atan2(light[0].position.x, 
										light[1].position.y - 
										light[0].position.y) * 180 / PI;
				console.setString(std::to_string(angleReflection));
				reflection_x = window.getSize().x;
				reflection_y = light[0].position.y - window.getSize().x / tan(angleReflection * PI / 180) * 1.5;
				reflection_y = window.getSize().y - reflection_y;
			} else {
				angleReflection = atan2(light[0].position.x, 
										light[1].position.y - 
										light[0].position.y) * 180 / PI;
				console.setString(std::to_string(angleReflection));
				reflection_x = (window.getSize().y - light[1].position.y) * tan(angleReflection * PI / 180);
				reflection_y = window.getSize().y;
			}
		} else {
			console.setString("4");
			y = window.getSize().y;
			x = y / 2 / tan(angleTorch * PI / 180 * -1) + window.getSize().x / 2;

			step = window.getSize().x / 3;
			if (x <= step) {
				angleReflection = atan2(light[0].position.y, 
										light[0].position.x - 
										light[1].position.x) * 180 / PI;
				console.setString(std::to_string(angleReflection));
				reflection_x = 0;
				reflection_y = light[1].position.x * tan(angleReflection * PI / 180);
				reflection_y = window.getSize().y - reflection_y;
			} else if (x <= window.getSize().x / 2) {
				angleReflection = atan2(light[0].position.y, 
										light[0].position.x - 
										light[1].position.x) * 180 / PI;
				console.setString(std::to_string(angleReflection));
				reflection_x = light[0].position.x - window.getSize().y / tan(angleReflection * PI / 180) * 1.5;
				reflection_y = 0;
			} else if (x <= step * 2) {
				angleReflection = atan2(light[0].position.y, 
										light[1].position.x - 
										light[0].position.x) * 180 / PI;
				console.setString(std::to_string(angleReflection));
				reflection_x = light[0].position.x - window.getSize().y / tan(angleReflection * PI / 180) * 1.5;
				reflection_y = 0;
				reflection_x = window.getSize().x - reflection_x;
			} else {
				angleReflection = atan2(light[0].position.y, 
										light[1].position.x - 
										light[0].position.x) * 180 / PI;
				console.setString(std::to_string(angleReflection));
				reflection_x = window.getSize().x;
				reflection_y = (reflection_x - light[1].position.x) * tan(angleReflection * PI / 180);
				reflection_y = window.getSize().y - reflection_y;
			}
		}
		light[1] = Vertex(Vector2f(x, y), Color::Yellow);
		reflection[1] = Vertex(Vector2f(reflection_x, reflection_y), Color::Yellow);
		reflection[0] = light[1];

		////////// DRAW ////////////////////////////////////////

		window.clear();
		window.draw(light, 2, Lines);
		window.draw(reflection, 2, Lines);
		window.draw(console);
		window.draw(torch);
		window.display();
	}
	
}
