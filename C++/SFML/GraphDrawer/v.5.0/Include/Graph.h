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
	vector<Connection*>	connectionPath;
	vector<Node*>		nodePath;
	Node* 				startNode;
	Node* 				endNode;
	bool 				ConnectionIsActive;
	bool 				InputWaiting;
	bool 				StartSelected;
	bool 				EndSelected;
	Theme 				theme;
	vector<char> 		actions;


public:

			Graph ();
			Graph (int width, int height, string title="Graph Drawer");
			~Graph ();
	void 	setTheme (string name);
	void 	setNodeTheme (string name);
	void 	setConnectionTheme (string name);
	void 	setInputBoxTheme (string name);
	bool	run ();
	void 	update ();
	void 	draw ();

private:

	void 	undo (string option);
	void 	click (Vector2f mouse_position);
	void 	writeInput ();
	bool 	findNode (Vector2f position, Node **foundNode);
	bool 	findConnection (Node *start, Node *end, float *weight);
	bool 	findConnection (Node *start, Node *end, Connection **foundConnection);
	void 	HandleConnection ();
	void 	FindPath ();

};