#include "Node.h"

Node::Node (Vector2f position, int index, NodeTheme &theme) {
	point.setPosition(position);
	this->index = index;
	setTheme(theme);
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

void Node::setSelected (bool selected) {
	this->selected = selected;
	if (selected) {
		point.setFillColor(theme->selectedColor);
		number.setFillColor(theme->selectedTextColor);
	} else {
		point.setFillColor(theme->pointColor);
		number.setFillColor(theme->textColor);
	}
}

void Node::setTheme (NodeTheme &theme) {
	this->theme = &theme;
	point.setRadius(theme.pointSize);
	point.setOrigin(point.getRadius(), point.getRadius());
	point.setFillColor(theme.pointColor);

	number.setFont(theme.font);
	number.setCharacterSize(theme.textSize);
	number.setFillColor(theme.textColor);
	number.setString(to_string(index));
	number.setOrigin(number.getLocalBounds().width/2, number.getLocalBounds().height/2 + number.getCharacterSize()/5);
	number.setPosition(point.getPosition());
}

void Node::draw (RenderWindow &window) {
	window.draw(point);
	window.draw(number);
}
