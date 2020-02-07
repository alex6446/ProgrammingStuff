#include "Connection.h"

Connection::Connection (Node *start, Node *end) {
	setup();
	setStartNode(start);
	setEndNode(end);
}

Connection::Connection (Node *start) {
	setup();
	setStartNode(start);
}

void Connection::setStartNode (Node *start) {
	this->start = start;
	line.append(Vertex(start->getPosition(), Color(239, 61, 89)));
	line.append(Vertex(start->getPosition(), Color(239, 61, 89)));
	triangle.setPosition(start->getPosition());
	triangle.setFillColor(Color(239, 61, 89));
}

void Connection::setEndNode (Node *end) {
	this->end = end;
	line[0].color = Color(239, 238, 238)  ;
	line[1].position = end->getPosition();
	line[1].color = Color(239, 238, 238)  ;
	triangle.setFillColor(Color(239, 238, 238)  );
	triangle.setPosition(end->getPosition());
	normalize_arrow(triangle.getRadius() + end->getRadius());
}

void Connection::setEndPosition (Vector2f position) {
	line[1].position = position;
	triangle.setPosition(position);
	normalize_arrow(triangle.getRadius());
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

void Connection::draw (RenderWindow &window) {
	window.draw(line);
	window.draw(triangle);
	if (view_weight)
		window.draw(text);
}

void Connection::setup () {
	view_weight = false;
	triangle.setRadius(7);
	triangle.setPointCount(3);
	triangle.setOrigin(triangle.getRadius(), triangle.getRadius());
	line.setPrimitiveType(LinesStrip);

	font.loadFromFile("Fonts/Terminus-Bold.ttf");
	text.setFont(font);
	text.setCharacterSize(16);
	text.setFillColor(Color(239, 238, 238));
}

void Connection::normalize_arrow (float scale) {
	Vector2f sides = Vector2f(line[1].position) - 
					 Vector2f(line[0].position);
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
	//cout << text.getLocalBounds().height << endl;
	Vector2f position = Vector2f(line[0].position + line[1].position)/2.f;
	Vector2f sides = Vector2f(line[0].position) - Vector2f(line[1].position);
	int angle = atan2(sides.y, sides.x) * 180 / PI * -1 + 180;
	if (angle > 90 && angle < 270) angle += 180;
	//text.setOrigin(Vector2f(text.getLocalBounds().height/2, 0));
	text.setPosition(position);
	text.setRotation(-angle);
}

