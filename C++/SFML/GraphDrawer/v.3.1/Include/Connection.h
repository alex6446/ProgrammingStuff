#pragma once

#include <iostream>
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
	Color 			activeColor;
	Color 			finalColor;
	Text 			text;
	float 			weight;
	bool 			view_weight;
	bool			is_set;

public:

			Connection (Node *start, Node *end, Font &font);
			Connection (Node *start, Font &font);

	Node* 	getStartNode ();
	Node* 	getEndNode ();
	float 	getWeight ();

	void 	setStartNode (Node *start);
	void 	setEndNode (Node *end);
	void 	setEndPosition (Vector2f position);
	void 	setWeight (string weight);
	void 	setWeight (float weight);

	void 	setArrowSzie (int size);
	void	setFont (Font &font);
	void 	setActiveColor (Color &color);
	void 	setFinalColor (Color &color);
	void 	setTextColor (Color &color);
	void 	setFontSize (int size);
	
	void 	draw (RenderWindow &window);

private:

	void 	setup ();
	void 	normalize_arrow (float scale, Vector2f position);
	void 	normalize_text ();

};