#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Node {
private:
	
	int 		index;
	CircleShape point;
	Text 		number;
	Font 		font;

public:

				Node (Vector2f position, int index);
	Vector2f 	getPosition ();
	int 		getIndex ();
	int 		getRadius ();
	void 		setRadius (int raduis);
	void		setFont (Font &font);
	void 		draw (RenderWindow &window);

private:

	void 		setup ();
};