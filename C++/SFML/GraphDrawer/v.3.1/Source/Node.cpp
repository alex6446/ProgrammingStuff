#include "Node.h"

Node::Node (Vector2f position, int index, Font &font) {
	point.setPosition(position);
	this->index = index;
	number.setFont(font);
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

void Node::setFont (Font &font) {
	number.setFont(font);
}

void Node::setNodeColor (Color &color) {
	point.setFillColor (color);
}

void Node::setTextColor (Color &color) {
	number.setFillColor (color);
}

void Node::setFontSize (int size) {
	number.setCharacterSize(size);
}

void Node::draw (RenderWindow &window) {
	window.draw(point);
	window.draw(number);
}

void Node::setup () {
	point.setRadius(14);
	point.setOrigin(point.getRadius(), point.getRadius());
	point.setFillColor(Color(74, 177, 157));

	number.setCharacterSize(18);
	number.setFillColor(Color(40, 92, 82));
	number.setString(to_string(index));
	number.setOrigin(number.getLocalBounds().width/2, number.getLocalBounds().height/2 + number.getCharacterSize()/5);
	number.setPosition(point.getPosition());
}
