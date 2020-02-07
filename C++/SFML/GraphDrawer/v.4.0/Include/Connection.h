#pragma once

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "Node.h"
#include "ConnectionTheme.h"

using namespace std;
using namespace sf;

#define PI 3.14159265

class Connection {
private:

	Node 			*start;
	Node 			*end;
	VertexArray 	line;
	CircleShape		triangle;
	Text 			text;
	float 			weight;
	bool 			view_weight;
	bool			is_set;

	ConnectionTheme* 	theme;

public:

			Connection (Node *start, ConnectionTheme &theme);

	Node* 	getStartNode ();
	Node* 	getEndNode ();
	float 	getWeight ();

	void 	setStartNode (Node *start);
	void 	setEndNode (Node *end);
	void 	setEndPosition (Vector2f position);
	void 	setWeight (string weight);
	void 	setWeight (float weight);
	void 	setTheme (ConnectionTheme &theme);
	
	void 	draw (RenderWindow &window);

private:

	void 	setup ();
	void 	normalize_arrow (float scale);
	void 	normalize_text ();

};