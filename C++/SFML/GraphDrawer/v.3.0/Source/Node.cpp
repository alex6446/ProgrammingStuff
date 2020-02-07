#include "Node.h"

Node::Node (Vector2f position, int index) {
	point.setPosition(position);
	this->index = index;
	setup();
}

Vector2f Node::getPosition () { 
	return point.getPosition(); 
}

int Node::getIndex () { 
	return index; 
}

int Node::getRadius () { 
	return point.getRadius(); 
}

void Node::setRadius (int raduis) { 
	point.setRadius(raduis); 
}

void Node::draw (RenderWindow &window) {
	window.draw(point);
	window.draw(number);
}

void Node::setup () {
	point.setRadius(14);
	point.setOrigin(point.getRadius(), point.getRadius());
	point.setFillColor(Color(74, 177, 157));

	font.loadFromFile("Fonts/Terminus-Bold.ttf");
	number.setFont(font);
	number.setCharacterSize(18);
	number.setFillColor(Color(40, 92, 82));
	number.setString(to_string(index));
	number.setOrigin(number.getLocalBounds().width/2, number.getLocalBounds().height/2 + number.getCharacterSize()/5);
	number.setPosition(point.getPosition());
}
