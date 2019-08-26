#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>

#define PI 3.14159265

using namespace sf;
using namespace std;

struct LineObject
{
	Vertex cords[2];
	LineObject* currentWall;
	float angle;
};

class MapObjects {
private:

	int reflectionNumber;
	RenderWindow* window;
	Sprite* torch;
	LineObject TemplateLine;
	vector<LineObject> walls;
	vector<LineObject> lights;
	vector<LineObject> boundaries;
	Color wallsColor;
	Color lightsColor;
	Color boundariesColor;

public:

	MapObjects (RenderWindow* RWindow, Sprite* Storch) {

		torch = Storch;
		window = RWindow;
		wallsColor = Color::Blue;
		lightsColor = Color::Yellow;
		boundariesColor = Color::Blue;
		reflectionNumber = 1;
		setBoundaries();
		updateTorch();

	}

private:

	void setBoundaries () {

		Vector2f corner[4] = {
			Vector2f(-20.f, -20.f),
			Vector2f(window->getSize().x+20, -20.f),
			Vector2f(window->getSize().x+20, window->getSize().y+20),
			Vector2f(-20.f, window->getSize().y+20)
		};

		TemplateLine.cords[0] = Vertex(corner[0], boundariesColor);
		TemplateLine.cords[1] = Vertex(corner[1], boundariesColor);
		TemplateLine.angle = 0;
		boundaries.push_back(TemplateLine);
		TemplateLine.cords[0] = Vertex(corner[1], boundariesColor);
		TemplateLine.cords[1] = Vertex(corner[2], boundariesColor);
		TemplateLine.angle = 90;
		boundaries.push_back(TemplateLine);
		TemplateLine.cords[0] = Vertex(corner[2], boundariesColor);
		TemplateLine.cords[1] = Vertex(corner[3], boundariesColor);
		TemplateLine.angle = 0;
		boundaries.push_back(TemplateLine);
		TemplateLine.cords[0] = Vertex(corner[3], boundariesColor);
		TemplateLine.cords[1] = Vertex(corner[0], boundariesColor);
		TemplateLine.angle = 90;
		boundaries.push_back(TemplateLine);

	}

	void updateTorch () {

		Vector2f sides = Vector2f(torch->getPosition()) -
						 Vector2f(Mouse::getPosition((*window)));
		float angleTorch = atan2(sides.y, sides.x) * 180 / PI * -1 + 180;
		torch->setRotation(angleTorch * -1 + 135);

		TemplateLine.angle = angleTorch;
		TemplateLine.cords[0] = Vertex(torch->getPosition(), lightsColor);
		TemplateLine.currentWall = nullptr;

	}

	void updateLight () {

		vector<LineObject> bufferPositions;
		LineObject endPosition;

		for (int ref = 0; ref < reflectionNumber; ref++) {
			for (int i = 0; i < walls.size(); i++) {
				if (&walls[i] != TemplateLine.currentWall) {
					if (checkWall(TemplateLine.cords[0].position, TemplateLine.angle, walls[i].cords)) {
						endPosition.cords[1] = getDots(TemplateLine, walls[i]);
						endPosition.angle = getAngle(TemplateLine.angle, walls[i].angle);
						endPosition.currentWall = &walls[i];
						bufferPositions.push_back(endPosition);
					}
				}
			}
			if (!bufferPositions.empty()) {

				for (int i = 0; i < bufferPositions.size(); i++) {
					if (sqrt(pow(bufferPositions[i].cords[1].position.x - TemplateLine.cords[0].position.x, 2) +
							 pow(bufferPositions[i].cords[1].position.y - TemplateLine.cords[0].position.y, 2)) <
						sqrt(pow(endPosition.cords[1].position.x - TemplateLine.cords[0].position.x, 2) +
							 pow(endPosition.cords[1].position.y - TemplateLine.cords[0].position.y, 2))) {
						endPosition = bufferPositions[i];
					}
				}

				TemplateLine.cords[1] = Vertex(endPosition.cords[1].position, lightsColor);
				lights.push_back(TemplateLine);
				TemplateLine.cords[0] = TemplateLine.cords[1];
				TemplateLine.angle = endPosition.angle;
				TemplateLine.currentWall = endPosition.currentWall;
			} else {
				break;
			}
			bufferPositions.clear();
		}

		if (lights.size() < reflectionNumber)
			updateTorchLight();

	}

	void updateTorchLight () {

		Vector2f endPosition;

		for (int i = 0; i < boundaries.size(); i++) {
			if (checkWall(TemplateLine.cords[0].position, TemplateLine.angle, boundaries[i].cords)) {

				endPosition = getDots(TemplateLine, boundaries[i]);
			}
		}

		TemplateLine.cords[1] = Vertex(endPosition, lightsColor);
		lights.push_back(TemplateLine);

	}

	bool checkWall (Vector2f lightPos, float lightAngle, Vertex wallPos[2]) {

		Vector2f sides1 = Vector2f(lightPos) -
						 Vector2f(wallPos[0].position);
		Vector2f sides2 = Vector2f(lightPos) -
						 Vector2f(wallPos[1].position);
		float angle1 = atan2(sides1.y, sides1.x) * 180 / PI * -1 + 180;
		float angle2 = atan2(sides2.y, sides2.x) * 180 / PI * -1 + 180;

		if (abs(angle1 - angle2) > 180) {
			if (lightAngle < min(angle1, angle2) || lightAngle > max(angle1, angle2)) {
				return true;
			}
		} else {
			if (lightAngle < max(angle1, angle2) && lightAngle > min(angle1, angle2)) {
				return true;
			}
		}

		return false;
	}

	Vector2f getDots(LineObject light, LineObject wall) {

		Vector2f wallBase = wall.cords[0].position;
		Vector2f lightBase = light.cords[0].position;
		Vector2f endPosition;
		Vector2f lightLevel; // point on light which has the same y as wallBase
		Vector2f sides;

		vector<Vector2f> endBuffer;

		float length; // distance between lightLevel and wallBase
		float xPosition; // x correction for endPosition
		float yPosition; // y correction for endPosition
		float ratio;

		float alpha = light.angle;
		float beta = wall.angle;
		float delta; // temp angle for check

		if (wall.cords[0].position.y < wall.cords[1].position.y)
			wallBase = wall.cords[1].position;

		endPosition.x = wallBase.x;
		endPosition.y = lightBase.y + abs(wallBase.x - lightBase.x)*tan(alpha / 180 * PI);

		sides = Vector2f(lightBase) - Vector2f(endPosition);
		delta = atan2(sides.y, sides.x) * 180 / PI * -1 + 180;

		if ((int)delta != (int)(alpha+0.001) && (int)(delta - 180) != (int)(alpha+0.001) && (int)(delta + 180) != (int)(alpha+0.001)) {
			endPosition.y = lightBase.y - (endPosition.y - lightBase.y);
		}

		lightLevel.y = wallBase.y;
		lightLevel.x = lightBase.x + abs(wallBase.y - lightBase.y)/tan(alpha / 180 * PI);

		sides = Vector2f(lightBase) - Vector2f(lightLevel);
		delta = atan2(sides.y, sides.x) * 180 / PI * -1 + 180;
		if ((int)delta != (int)alpha)
			lightLevel.x = lightBase.x - (lightLevel.x - lightBase.x);

		length = abs(lightLevel.x - wallBase.x);

		ratio = length*tan(alpha / 180 * PI)*sin((90 - beta) / 180 * PI)/sin((beta-alpha) / 180 * PI);

		xPosition = abs(ratio*cos(alpha / 180 * PI));
		yPosition = abs(ratio*sin(alpha / 180 * PI));

		if (alpha > -1 && alpha <= 1)
			if (beta < 90)
				endPosition = Vector2f(endPosition.x + xPosition, endPosition.y);
			else
				endPosition = Vector2f(endPosition.x - xPosition, endPosition.y);

		if (alpha > 1 && alpha < 90)
			if (beta < 90)
				endPosition = Vector2f(endPosition.x + xPosition, endPosition.y - yPosition);
			else
				endPosition = Vector2f(endPosition.x - xPosition, endPosition.y + yPosition);

		if (alpha == 90)
			endPosition = Vector2f(lightBase.x, wallBase.y - abs(length*tan(beta / 180 * PI)));

		if (alpha > 90 && alpha < 180)
			if (beta < 90)
				endPosition = Vector2f(endPosition.x + xPosition, endPosition.y + yPosition);
			else
				endPosition = Vector2f(endPosition.x - xPosition, endPosition.y - yPosition);

		if (alpha == 180)
			if (beta < 90)
				endPosition = Vector2f(endPosition.x + xPosition, endPosition.y);
			else
				endPosition = Vector2f(endPosition.x - xPosition, endPosition.y);

		if (alpha > 180 && alpha < 270)
			if (beta == 0)
				endPosition = Vector2f(endPosition.x - xPosition, endPosition.y + yPosition);
			else if (beta < 90)
				endPosition = Vector2f(endPosition.x + xPosition, endPosition.y - yPosition);
			else
				endPosition = Vector2f(endPosition.x - xPosition, endPosition.y + yPosition);

		if (alpha == 270)
			endPosition = Vector2f(lightBase.x, wallBase.y - abs(length*tan(beta / 180 * PI)));

		if (alpha > 270 && alpha < 360)
			if (beta == 0)
				endPosition = Vector2f(endPosition.x - xPosition, endPosition.y - yPosition);
			else if (beta < 90)
				endPosition = Vector2f(endPosition.x + xPosition, endPosition.y + yPosition);
			else
				endPosition = Vector2f(endPosition.x - xPosition, endPosition.y - yPosition);

		return endPosition;
	}

	float getAngle(float alpha, float beta) {

		float endPositionAngle = beta-alpha+beta;

		if (endPositionAngle < 0)
			endPositionAngle += 360;

		return endPositionAngle;
	}

public:

	void add_wall (Vector2f beginCord, Vector2f endCord) {

		add_wall(beginCord, endCord, wallsColor);

	}

	void add_wall (Vector2f beginCord, Vector2f endCord, Color color) {

		TemplateLine.cords[0] = Vertex(beginCord, color);
		TemplateLine.cords[1] = Vertex(endCord, color);

		if (beginCord.y < endCord.y)
			swap(beginCord, endCord);
		Vector2f sides = Vector2f(beginCord) - Vector2f(endCord);
		float angle = atan2(sides.y, sides.x) * 180 / PI * -1 + 180;
		TemplateLine.angle = angle;

		walls.push_back(TemplateLine);

	}

	void remove_wall () {
		if (!walls.empty())
			walls.pop_back();
	}

	void remove_walls () {
		walls.clear();
	}

	void set_wallsColor (Color color) {
		wallsColor = color;
	}

	void set_lightsColor (Color color) {
		lightsColor = color;
	}

	void set_reflectionNumber (int n) {
		reflectionNumber = n;
	}

	void update() {

		lights.clear();
		updateTorch();
		updateLight();

	}

	void draw () {

		for (int i = 0; i < boundaries.size(); i++)
			window->draw(boundaries[i].cords, 2, Lines);
		for (int i = 0; i < walls.size(); i++)
			window->draw(walls[i].cords, 2, Lines);
		for (int i = 0; i < lights.size(); i++)
			window->draw(lights[i].cords, 2, Lines);

	}

};

int main () {

	// Window
	RenderWindow window(VideoMode(1080, 920), "Reflection 2.0");
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

	// Variables
	MapObjects Surface(&window, &torch);
	Surface.set_reflectionNumber(150);

	/*Surface.add_wall(Vector2f(500, 200), Vector2f(700, 200));
	Surface.add_wall(Vector2f(700, 200), Vector2f(600, 600));
	Surface.add_wall(Vector2f(600, 600), Vector2f(400, 600));
	Surface.add_wall(Vector2f(400, 600), Vector2f(500, 200));*/

	bool MouseLeftButtonPressed = false;
	bool safeWall = false;
	LineObject newWall;

	// Main loop
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Escape)
					window.close();
				if (event.key.code == Keyboard::Z)
					Surface.remove_wall();
				if (event.key.code == Keyboard::X)
					Surface.remove_walls();
			}
			if (event.type == Event::MouseButtonPressed) {
				if (event.mouseButton.button == Mouse::Left){
					MouseLeftButtonPressed = true;
					newWall.cords[0] = Vertex(Vector2f(Mouse::getPosition(window)), Color::Red);
				}
			}
			if (event.type == Event::MouseButtonReleased) {
				if (event.mouseButton.button == Mouse::Left){
					MouseLeftButtonPressed = false;
					safeWall = false;
					Surface.add_wall(newWall.cords[0].position, newWall.cords[1].position, Color::Green);
				}
			}
		}

		//////////// UPDATE /////////////

		if (Keyboard::isKeyPressed(Keyboard::Right))
			torch.move(Vector2f(5.f, 0.f));
		else if (Keyboard::isKeyPressed(Keyboard::Left))
			torch.move(Vector2f(-5.f, 0.f));
		if (Keyboard::isKeyPressed(Keyboard::Up))
			torch.move(Vector2f(0.f, -5.f));
		else if (Keyboard::isKeyPressed(Keyboard::Down))
			torch.move(Vector2f(0.f, 5.f));

		if (MouseLeftButtonPressed) {
			newWall.cords[1] = Vertex(Vector2f(Mouse::getPosition(window)), Color::Red);
			safeWall = true;
		}

		Surface.update();

		////////////// DRAW ////////////////

		window.clear();
		Surface.draw();
		if (safeWall)
			window.draw(newWall.cords, 2, Lines);
		window.draw(torch);
		window.display();
	}

	return 0;
}
