#pragma once

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Node {
private:
	
	int 		index;
	Text 		number;
	CircleShape point;

public:

				Node (Vector2f position, int index, Font &font);
	Vector2f 	getPosition ();
	int 		getIndex ();
	int 		getRadius ();
	void 		setRadius (int raduis);
	void		setFont (Font &font);
	void 		setNodeColor (Color &color);
	void 		setTextColor (Color &color);
	void 		setFontSize (int size);
	void 		setTextSize (int size);
	void 		draw (RenderWindow &window);

private:

	void 		setup ();
};