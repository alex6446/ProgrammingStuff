#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "Node.h"

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
	Font			font;
	float 			weight;
	bool 			view_weight;

public:

			Connection (Node *start, Node *end);
			Connection (Node *start);

	void 	setStartNode (Node *start);
	void 	setEndNode (Node *end);
	void 	setEndPosition (Vector2f position);
	void 	setWeight (string weight);
	void 	setWeight (float weight);
	void 	setArrowSzie (int size);

	Node* 	getStartNode ();
	Node* 	getEndNode ();
	float 	getWeight ();
	
	void 	draw (RenderWindow &window);

private:

	void 	setup ();
	void 	normalize_arrow (float scale);
	void 	normalize_text ();

};