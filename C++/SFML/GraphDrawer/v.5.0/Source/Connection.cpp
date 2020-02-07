#include "Connection.h"

Connection::Connection (Node *start, ConnectionTheme &theme) {
	is_set = false;
	view_weight = false;
	line.setPrimitiveType(LinesStrip);
	triangle.setPointCount(3);
	setTheme(theme);
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
	line.append(Vertex(start->getPosition(), theme->activeColor));
	line.append(Vertex(start->getPosition(), theme->activeColor));
	triangle.setPosition(start->getPosition());
	triangle.setFillColor(theme->activeColor);
}

void Connection::setEndNode (Node *end) {
	is_set = true;
	this->end = end;
	line[0].color = theme->finalColor;
	line[1].position = end->getPosition();
	line[1].color = theme->finalColor;
	triangle.setFillColor(theme->finalColor);
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

void Connection::setTheme (ConnectionTheme &theme) {
	this->theme = &theme;
	triangle.setRadius(theme.arrowSize);
	triangle.setOrigin(triangle.getRadius(), triangle.getRadius());
	text.setFont(theme.font);
	text.setFillColor(theme.textColor);
	text.setCharacterSize(theme.textSize);
	if (is_set) {
		normalize_arrow(triangle.getRadius() + end->getRadius());
		normalize_text();
		line[0].color = theme.finalColor;
		line[1].color = theme.finalColor;
		triangle.setFillColor(theme.finalColor);
	} else {
		if (line.getVertexCount() == 2) {
			line[0].color = theme.activeColor;
			line[1].color = theme.activeColor;
		}
		triangle.setFillColor(theme.activeColor);
	}
}

void Connection::setHighlighted (bool highlighted) {
	this->highlighted = highlighted;
	if (highlighted) {
		line[0].color = theme->highlightColor;
		line[1].color = theme->highlightColor;
		triangle.setFillColor(theme->highlightColor);
		text.setFillColor(theme->highlightTextColor);
	} else {
		line[0].color = theme->finalColor;
		line[1].color = theme->finalColor;
		triangle.setFillColor(theme->finalColor);
		text.setFillColor(theme->textColor);
	}
}

void Connection::draw (RenderWindow &window) {
	window.draw(line);
	window.draw(triangle);
	if (view_weight)
		window.draw(text);
}

void Connection::normalize_arrow (float scale) {
	Vector2f sides = line[1].position - line[0].position;
	float angle_rad = atan2(sides.y, sides.x);
	float angle = atan2(sides.y, sides.x) * 180 / PI * -1 + 180;
	float length = sqrt(pow(sides.x, 2) + pow(sides.y, 2)) - scale;
	triangle.setPosition(Vector2f(
		line[0].position.x+cos(angle_rad)*length,
		line[0].position.y+sin(angle_rad)*length));
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

