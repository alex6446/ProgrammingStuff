#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

#define PI 3.14159265

class Node {
private:

	int index;
	CircleShape point;
	Text text;
	Font font;

public:

	Node (Vector2f position, int index) {
		this->index = index;
		point.setPosition(position);
		setup();
	}

	Vector2f getPosition () { return point.getPosition(); }
	void setRadius (int raduis) { point.setRadius(raduis); }
	int getRadius () { return point.getRadius(); }
	int getIndex () { return index; }

	void draw (RenderWindow &window) {
		window.draw(point);
		window.draw(text);
	}

private:

	void setup () {
		point.setRadius(14);
		point.setOrigin(point.getRadius(), point.getRadius());
		point.setFillColor(Color::Green);

		font.loadFromFile("Terminus-Bold.ttf");
		text.setFont(font);
		text.setCharacterSize(18);
		text.setFillColor(Color::Black);
		text.setString(to_string(index));
		text.setOrigin(text.getLocalBounds().width/2, text.getLocalBounds().height/2+text.getCharacterSize()/5);
		text.setPosition(point.getPosition());
	}

};


class Connection {
private:

	Node *start;
	Node *end;
	VertexArray line;
	CircleShape arrow;
	Text text;
	Font font;
	float weight;
	bool viewWeight;

public:

	Connection (Node *start, Node *end) {
		setup();
		setStartNode(start);
		setEndNode(end);
	}

	Connection (Node *start) {
		setup();
		setStartNode(start);
	}

	void setArrowSzie (int size) {
		arrow.setRadius(size);
	}

	void setStartNode (Node *start) {
		this->start = start;
		line.append(Vertex(start->getPosition(), Color::Red));
		line.append(Vertex(start->getPosition(), Color::Red));
		arrow.setPosition(start->getPosition());
		arrow.setFillColor(Color::Red);
	}

	void setEndNode (Node *end) {
		this->end = end;
		line[0].color = Color::White;
		line[1].position = end->getPosition();
		line[1].color = Color::White;
		arrow.setFillColor(Color::White);
		arrow.setPosition(end->getPosition());
		normalize_arrow(arrow.getRadius() + end->getRadius());
	}

	void setEndPosition (Vector2f position) {
		line[1].position = position;
		arrow.setPosition(position);
		normalize_arrow(arrow.getRadius());
	}

	void setWeight (string weight) {
		viewWeight =true;
		this->weight = stof(weight);
		text.setString(weight);
		normalize_text();
	}

	void setWeight (float weight) { this->weight = weight; }
	float getWeight () { return weight; }

	Node* getStart () { return start; }
	Node* getEnd () { return end; }

	void draw (RenderWindow &window) {
		window.draw(line);
		window.draw(arrow);
		if (viewWeight)
			window.draw(text);
	}

private:

	void setup () {
		viewWeight = false;
		arrow.setRadius(7);
		arrow.setPointCount(3);
		arrow.setOrigin(arrow.getRadius(), arrow.getRadius());
		line.setPrimitiveType(LinesStrip);

		font.loadFromFile("Terminus-Bold.ttf");
		text.setFont(font);
		text.setCharacterSize(16);
		text.setFillColor(Color::White);
	}

	void normalize_arrow (float scale) {
		Vector2f sides = Vector2f(line[1].position) - 
						 Vector2f(line[0].position);
		float angle_rad = atan2(sides.y, sides.x);
		float angle = atan2(sides.y, sides.x) * 180 / PI * -1 + 180;
		float length = sqrt(pow(sides.x, 2) + pow(sides.y, 2)) - scale;
		line[1].position = Vector2f(
			line[0].position.x+cos(angle_rad)*length,
			line[0].position.y+sin(angle_rad)*length);
		arrow.setPosition(line[1].position);
		arrow.setRotation(-angle+30);
	}

	void normalize_text () {
		//cout << text.getLocalBounds().height << endl;
		Vector2f position = Vector2f(line[0].position + line[1].position)/2.f;
		Vector2f sides = Vector2f(line[0].position) - Vector2f(line[1].position);
		int angle = atan2(sides.y, sides.x) * 180 / PI * -1 + 180;
		if (angle > 90 && angle < 270) angle += 180;
		//text.setOrigin(Vector2f(text.getLocalBounds().height/2, 0));
		text.setPosition(position);
		text.setRotation(-angle);
		cout << angle << endl;
	}
};


class InputBox {
private:

	RenderWindow window;
	Font font;
	Text text;
	string input;
	Connection* connection;

public:

	InputBox () {
		font.loadFromFile("Terminus-Bold.ttf");
		text.setFont(font);
		text.setCharacterSize(24);
		text.setFillColor(Color(30, 197, 3));
	};

	bool isActive () { return window.isOpen(); }

	void inputWeight (Connection *connection) {
		this->connection = connection;
		window.create(VideoMode(180, 80), "Weight", Style::Close);
		window.setPosition(Vector2i(VideoMode::getDesktopMode().width/2 - window.getSize().x/2, 
    				   				VideoMode::getDesktopMode().height/2 - window.getSize().y/2));
		input = "0";
		update_text();
	}

	void update () {
		if (window.isOpen()) {
			Event event;
			while(window.pollEvent(event)) {
				if (event.type == Event::Closed)
					update_weight();
				if (event.type == Event::TextEntered) {
					if(event.text.unicode > 31) {
						if (input == "0") input.clear();
						input += event.text.unicode;
						update_text();
					}
				} else
				if (event.type == Event::KeyPressed) {
					if (event.key.code == Keyboard::Backspace)
						if (input.size()) {
							input.erase(input.size()-1);
							update_text();
						} 
					if (event.key.code == Keyboard::Enter)
						update_weight();
				}
			}
		}
	}

	void draw () {
		if (window.isOpen()) {
			window.clear();
			window.draw(text);
			window.display();
		}
	}
private:
	void update_text () {
		text.setString(input);
		text.setPosition(
			window.getSize().x/2 - text.getLocalBounds().width/2, 
			window.getSize().y/2 - text.getLocalBounds().height/2
		);
	}
	void update_weight () {
		window.close();
		connection->setWeight(input);
	}
};


class Net {
private:

	vector<Node> nodes;
	vector<Connection> connections;
	bool ConnectionIsActive;
	InputBox inputBox;

public:

	Net () { ConnectionIsActive = false; }

	void click (Vector2f mouse_position) {
		if (!inputBox.isActive()) {
			Node* selectedNode;
			bool NodeHit = findNode(mouse_position, &selectedNode);
			if (NodeHit) {
				if (!ConnectionIsActive) {
					ConnectionIsActive = true;
					connections.push_back(Connection(selectedNode));
				} else {
					ConnectionIsActive = false;
					connections.back().setEndNode(selectedNode);
					HandleConnection();
				}
			} else {
				if (!ConnectionIsActive) {
					nodes.push_back(Node(mouse_position, nodes.size()+1));
				} else {
					ConnectionIsActive = false;
					connections.pop_back();
				}
			}
		}
	}

	void update (Vector2f mouse_position) {
		if (ConnectionIsActive) {
			connections.back().setEndPosition(mouse_position);
		}
		inputBox.update();
	}

	void draw (RenderWindow &window) {
		for (auto connection : connections) connection.draw(window);
		for (auto node : nodes) node.draw(window);
		inputBox.draw();
	}

private:

	bool findNode (Vector2f position, Node **foundNode) {
		for (auto &node : nodes)
			if (sqrt(pow(position.x - node.getPosition().x, 2) +
			 	pow(position.y - node.getPosition().y, 2)) <= 
				node.getRadius()) {
				*foundNode = &node; 
				return true;
			}
		return false;
	}

	void HandleConnection () {
		for (int i = 0; i < connections.size()-1; i++) {
			if (connections[i].getStart() == connections.back().getStart() && 
				connections[i].getEnd() == connections.back().getEnd()) {
				connections.pop_back();
				return;
			}
			if (connections[i].getStart() == connections.back().getEnd() && 
				connections[i].getEnd() == connections.back().getStart()) {
				connections.back().setWeight(connections[i].getWeight());
				return;
			}
		}
		inputBox.inputWeight(&connections.back());
	}
};


int main () {

	RenderWindow window(VideoMode(800, 520), "Arrows");
   window.setPosition(Vector2i(
	VideoMode::getDesktopMode().width/2 - window.getSize().x/2,
	VideoMode::getDesktopMode().height/2 - window.getSize().y/2));

	Net net;

	while (window.isOpen()) {
		
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Escape)
					window.close();
				/*if (event.key.code == Keyboard::Z)
					if (!PointActive && !edges.empty())
						edges.pop_back();
				if (event.key.code == Keyboard::X)
					if (!PointActive && !edges.empty())
						edges.clear();*/
			}
			if (event.type == Event::MouseButtonPressed) {
				if (event.mouseButton.button == Mouse::Left) {
					net.click(Vector2f(Mouse::getPosition(window)));
				}
			}
		}

		net.update(Vector2f(Mouse::getPosition(window)));

		window.clear();
		net.draw(window);
		window.display();
	}
}
