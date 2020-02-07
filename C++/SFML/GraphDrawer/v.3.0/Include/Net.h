#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "Node.h"
#include "Connection.h"
#include "InputBox.h"

using namespace std;
using namespace sf;

class Net {
private:

	vector<Node*> 		nodes;
	vector<Connection*>	connections;
	bool 				ConnectionIsActive;
	InputBox 			inputBox;

public:

			Net ();
			//~Net ();
	void 	click (Vector2f mouse_position);
	void 	update (Vector2f mouse_position);
	void 	draw (RenderWindow &window);

private:

	bool 	findNode (Vector2f position, Node **foundNode);
	void 	HandleConnection ();

};