#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Node.h"
#include "Connection.h"
#include "InputBox.h"

#include "ThemeEngine.h"

using namespace std;
using namespace sf;

class Graph {
private:

	RenderWindow		window;
	InputBox 			inputBox;
	vector<Node*> 		nodes;
	vector<Connection*>	connections;
	bool 				ConnectionIsActive;
	bool 				InputWaiting;
	Theme 				theme;


public:

			Graph ();
			Graph (int width, int height, string title="Graph Drawer");
	void 	setTheme (string name);
	void 	setNodeTheme (string name);
	void 	setConnectionTheme (string name);
	void 	setInputBoxTheme (string name);
	bool	run ();
	void 	update ();
	void 	draw ();

private:

	void 	click (Vector2f mouse_position);
	void 	writeInput ();
	bool 	findNode (Vector2f position, Node **foundNode);
	void 	HandleConnection ();

};