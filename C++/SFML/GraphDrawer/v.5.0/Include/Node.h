#pragma once

#include <SFML/Graphics.hpp>
#include "NodeTheme.h"

using namespace std;
using namespace sf;

class Node {
private:
	
	int 		index;
	Text 		number;
	CircleShape point;
	NodeTheme*	theme;
	bool 		selected;

public:

				Node (Vector2f position, int index, NodeTheme &theme);
	Vector2f 	getPosition ();
	int 		getIndex ();
	int 		getRadius ();
	void 		setSelected (bool selected);
	void		setTheme (NodeTheme &theme);
	void 		draw (RenderWindow &window);

};