#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

#define PI 3.14159265

struct Point {
	int index;
	CircleShape dot;
	Point () {
		dot.setRadius(10);
		dot.setOrigin(dot.getRadius(), dot.getRadius());
	}
};

struct Edge {
	VertexArray line;
	CircleShape triangle;
	Edge () {
		triangle.setRadius(7);
		triangle.setPointCount(3);
		triangle.setOrigin(triangle.getRadius(), triangle.getRadius());
		line.setPrimitiveType(LinesStrip);
	}
};

int main()
{
    RenderWindow window(VideoMode(800, 520), "Arrows");
    window.setPosition(Vector2i(
	VideoMode::getDesktopMode().width/2 - window.getSize().x/2,
	VideoMode::getDesktopMode().height/2 - window.getSize().y/2));
    Font font;
    font.loadFromFile("Terminus-Bold.ttf");

    int index = 1;
    bool PointActive = false;
    vector<Point> points;
    vector<Edge> edges;
    Edge edge;
    Point point;

	while (window.isOpen()) {
		
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Escape)
					window.close();
				if (event.key.code == Keyboard::Z)
					if (!PointActive && !edges.empty())
						edges.pop_back();
				if (event.key.code == Keyboard::X)
					if (!PointActive && !edges.empty())
						edges.clear();
			}
			if (event.type == Event::MouseButtonPressed) {
				if (event.mouseButton.button == Mouse::Left){
					bool OnPoint = false;
					Vector2f DotPosition;
					Vector2f MousePosition = Vector2f(Mouse::getPosition(window));
					if (!points.empty())
						for (auto &i : points) {
							if (sqrt(pow(MousePosition.x - i.dot.getPosition().x, 2) +
							 	pow(MousePosition.y - i.dot.getPosition().y, 2)) <= 
								i.dot.getRadius()) {
								OnPoint = true;
								DotPosition = i.dot.getPosition();
							}
						}
					if (OnPoint)
						if (!PointActive) {
							PointActive = true;
							edge.line.append(Vertex(DotPosition, Color::Red));
							edge.line.append(Vertex(DotPosition, Color::White));
							edge.triangle.setFillColor(Color::Red);
						} else {
							PointActive = false;
							edge.line[0].color = Color::White;
							edge.line[1] = Vertex(DotPosition, Color::White);
							edge.triangle.setFillColor(Color::White);
							Vector2f sides = Vector2f(edge.line[1].position) - 
											 Vector2f(edge.line[0].position);
							float angle_rad = atan2(sides.y, sides.x);
							float angle = atan2(sides.y, sides.x) * 180 / PI * -1 + 180;
							float length = sqrt(pow(sides.x, 2) + pow(sides.y, 2))-
												point.dot.getRadius()-edge.triangle.getRadius();
							edge.line[1].position = Vector2f(
								edge.line[0].position.x+cos(angle_rad)*length,
								edge.line[0].position.y+sin(angle_rad)*length);
							cout << cos(angle_rad) << " " << length << " " << point.dot.getRadius() << endl;
							edge.triangle.setPosition(edge.line[1].position);
							edge.triangle.setRotation(-angle+30);
							edges.push_back(edge);
							edge.line.clear();
						}
					else {
						if (!PointActive) {
							point.index = index++;
							point.dot.setPosition(MousePosition);
							point.dot.setFillColor(Color::Green);
							points.push_back(point);
						} else {
							PointActive = false;
							edge.line.clear();
						}
					}
				}
			}
		}

		if (PointActive) {
			edge.line[1] = Vertex(Vector2f(Mouse::getPosition(window)), Color::Red);
			edge.triangle.setPosition(edge.line[1].position);
			Vector2f sides = Vector2f(edge.line[1].position) - 
							 Vector2f(edge.line[0].position);
			float angle = atan2(sides.y, sides.x) * 180 / PI * -1 + 180;
			edge.triangle.setRotation(-angle+30);
		}

		window.clear();
		if (PointActive) {
			window.draw(edge.line);
			window.draw(edge.triangle);
		}
		if (!edges.empty())
			for (auto &i : edges) {
				window.draw(i.line);
				window.draw(i.triangle);
			}
		if (!points.empty())
			for (auto &i : points)
				window.draw(i.dot);
		window.display();
	}
    return 0;
}
