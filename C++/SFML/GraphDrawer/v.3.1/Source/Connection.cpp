#include "Connection.h"

Connection::Connection (Node *start, Node *end, Font &font) {
	text.setFont(font);
	setup();
	setStartNode(start);
	setEndNode(end);
}

Connection::Connection (Node *start, Font &font) {
	text.setFont(font);
	setup();
	setStartNode(start);
}

Node* Connection::getStartNode () { 
	return start; 
}

Node* Connection::getEndNode () { 
	return end; 
}

float Connection::getWeight () { 
	return weight; 
}

void Connection::setStartNode (Node *start) {
	this->start = start;
	line.append(Vertex(start->getPosition(), activeColor));
	line.append(Vertex(start->getPosition(), activeColor));
	triangle.setPosition(start->getPosition());
	triangle.setFillColor(activeColor);
}

void Connection::setEndNode (Node *end) {
	is_set = true;
	this->end = end;
	line[0].color = finalColor;
	line[1].position = end->getPosition();
	line[1].color = finalColor;
	triangle.setFillColor(finalColor);
	triangle.setPosition(end->getPosition());
	normalize_arrow(triangle.getRadius() + end->getRadius(), line[1].position);
}

void Connection::setEndPosition (Vector2f position) {
	line[1].position = position;
	triangle.setPosition(position);
	normalize_arrow(triangle.getRadius(), line[1].position);
}

void Connection::setWeight (string weight) {
	view_weight =true;
	this->weight = stof(weight);
	text.setString(weight);
	normalize_text();
}

void Connection::setWeight (float weight) { 
	this->weight = weight; 
}

void Connection::setArrowSzie (int size) {
	triangle.setRadius(size);
	if (is_set) {
		normalize_arrow(triangle.getRadius() + end->getRadius(), end->getPosition());
		normalize_text();
	}
}

void Connection::setFont (Font &font) {
	text.setFont(font);
	if (is_set)
		normalize_text();
}

void Connection::setActiveColor (Color &color) {
	activeColor = color;
	if (!is_set) {
		line[0].color = activeColor;
		line[1].color = activeColor;
		triangle.setFillColor(activeColor);
	}
}

void Connection::setFinalColor (Color &color) {
	finalColor = color;
	if (is_set) {
		line[0].color = finalColor;
		line[1].color = finalColor;
		triangle.setFillColor(finalColor);
	}
}

void Connection::setTextColor (Color &color) {
	text.setFillColor(color);
}

void Connection::setFontSize (int size) {
	text.setCharacterSize(size);
	if (is_set)
		normalize_text();
}

void Connection::draw (RenderWindow &window) {
	window.draw(line);
	window.draw(triangle);
	if (view_weight)
		window.draw(text);
}

void Connection::setup () {
	is_set = false;
	view_weight = false;
	activeColor = Color(239, 61, 89);
	finalColor = Color(239, 238, 238);

	triangle.setRadius(7);
	triangle.setPointCount(3);
	triangle.setOrigin(triangle.getRadius(), triangle.getRadius());
	line.setPrimitiveType(LinesStrip);

	text.setCharacterSize(16);
	text.setFillColor(finalColor);
}

void Connection::normalize_arrow (float scale, Vector2f position) {
	Vector2f sides = position - Vector2f(line[0].position);
	float angle_rad = atan2(sides.y, sides.x);
	float angle = atan2(sides.y, sides.x) * 180 / PI * -1 + 180;
	float length = sqrt(pow(sides.x, 2) + pow(sides.y, 2)) - scale;
	line[1].position = Vector2f(
		line[0].position.x+cos(angle_rad)*length,
		line[0].position.y+sin(angle_rad)*length);
	triangle.setPosition(line[1].position);
	triangle.setRotation(-angle+30);
}

void Connection::normalize_text () {
	Vector2f position = Vector2f(line[0].position + line[1].position)/2.f;
	Vector2f sides = Vector2f(line[0].position) - Vector2f(line[1].position);
	int angle = atan2(sides.y, sides.x) * 180 / PI * -1 + 180;
	if (angle > 90 && angle < 270) angle += 180;
	text.setOrigin(Vector2f(text.getLocalBounds().width/2, 0));
	text.setPosition(position);
	text.setRotation(-angle);
}

