#include "Graph.h"

Graph::Graph () { 
	EndSelected = false;
	StartSelected = false;
	InputWaiting = false;
	ConnectionIsActive = false;
	window.create(VideoMode::getDesktopMode(), "Graph Drawer");
	LoadThemes();
	setTheme("Default");
}

Graph::Graph (int width, int height, string title) {
	EndSelected = false;
	StartSelected = false;
	InputWaiting = false;
	ConnectionIsActive = false;
	window.create(VideoMode(width, height), title, sf::Style::Close);
	window.setPosition(Vector2i(
		VideoMode::getDesktopMode().width/2 - window.getSize().x/2,
		VideoMode::getDesktopMode().height/2 - window.getSize().y/2));
	LoadThemes();
	setTheme("Default");
};

Graph::~Graph () {
	for (auto &node : nodes)
		delete node;
	for (auto &connection : connections)
		delete connection;
}

void Graph::setTheme (string name) {
	theme = GetTheme(name);
	inputBox.setTheme(theme.ibox);
	for (auto node : nodes)
		node->setTheme(theme.node);
	for (auto connection : connections)
		connection->setTheme(theme.connection);
}

void Graph::setNodeTheme (string name) {
	theme.node = GetNodeTheme(name);
	for (auto node : nodes)
		node->setTheme(theme.node);
	for (auto connection : connections)
		connection->setTheme(theme.connection);
}

void Graph::setConnectionTheme (string name) {
	theme.connection = GetConnectionTheme(name);
	for (auto connection : connections)
		connection->setTheme(theme.connection);
}

void Graph::setInputBoxTheme (string name) {
	theme.ibox = GetInputBoxTheme(name);
	inputBox.setTheme(theme.ibox);
}


bool Graph::run () {
	return window.isOpen();
}

void Graph::update () {
	Vector2f mouse_position = Vector2f(Mouse::getPosition(window));
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed)
			window.close();
		if (event.type == Event::KeyPressed) {
			if (event.key.code == Keyboard::Escape)
				window.close();
			if (event.key.code == Keyboard::LControl)
				if (ConnectionIsActive) {
					ConnectionIsActive = false;
					connections.pop_back();
				}
			if (event.key.code == Keyboard::Z)
				if (Keyboard::isKeyPressed(Keyboard::LControl)) {
					undo("selection");
					undo("last");
				}
			if (event.key.code == Keyboard::X)
				if (Keyboard::isKeyPressed(Keyboard::LControl)) {
					undo("selection");
					undo("all");
				}
			if (event.key.code == Keyboard::S)
				if (Keyboard::isKeyPressed(Keyboard::LControl))
					undo("selection");
		}
		if (event.type == Event::MouseButtonPressed) {
			if (event.mouseButton.button == Mouse::Left) {
				if (!InputWaiting)
					click(mouse_position);
				else {
					inputBox.close();
					writeInput();
				}
			}
		}
	}

	if (ConnectionIsActive)
		connections.back()->setEndPosition(mouse_position);
	inputBox.update();
	if (InputWaiting && !inputBox.isActive())
		writeInput(); 
}

void Graph::draw () {
	window.clear(theme.backgroundColor);
	for (auto connection : connections) connection->draw(window);
	for (auto node : nodes) node->draw(window);
	inputBox.draw();
	window.display();
}

void Graph::undo (string option) {
	if (option == "last") {
		if (!InputWaiting) {
			if (!actions.empty()) {
				switch (actions.back()) {
				case 'c':
					if (!connections.empty()) 
						connections.pop_back();
					ConnectionIsActive = false;
					break;
				case 'n':
					if (!nodes.empty()) 
						nodes.pop_back();
					break;
				}
				actions.pop_back();
			}
		}
	}
	if (option == "all") {
		if (!InputWaiting) {
			if (!connections.empty())
				connections.clear();
			if (!nodes.empty())
				nodes.clear();
			ConnectionIsActive = false;
		}
	}
	if (option == "selection") {
		if (!InputWaiting) {
			if (StartSelected) {
				startNode->setSelected(false);
				StartSelected = false;
			}
			if (EndSelected) {
				endNode->setSelected(false);
				EndSelected = false;
				for (auto &connection : connectionPath)
					connection->setHighlighted(false);
				connectionPath.clear();
				for (auto &node : nodePath)
					node->setSelected(false);
				nodePath.clear();
			}
		}
	}
}

void Graph::click (Vector2f mouse_position) {
	if (!inputBox.isActive()) {
		Node* selectedNode;
		bool NodeHit = findNode(mouse_position, &selectedNode);
		if (NodeHit) {
			if (Keyboard::isKeyPressed(Keyboard::LControl)) {
				if (!StartSelected) {
					StartSelected = true;
					startNode = selectedNode;
					startNode->setSelected(true);
				} else if (selectedNode != startNode) {
					if (!EndSelected) {
						EndSelected = true;
						endNode = selectedNode;
						endNode->setSelected(true);
					} else if (selectedNode != endNode) {
						endNode->setSelected(false);
						endNode = selectedNode;
						endNode->setSelected(true);
					}
					FindPath();
				}
			} else {
				if (!ConnectionIsActive) {
					ConnectionIsActive = true;
					connections.push_back(new Connection(selectedNode, theme.connection));
				} else {
					ConnectionIsActive = false;
					connections.back()->setEndNode(selectedNode);
					HandleConnection();
					actions.push_back('c');
				}
			}
		} else {
			if (!Keyboard::isKeyPressed(Keyboard::LControl))
				if (!ConnectionIsActive) {
					nodes.push_back(new Node(mouse_position, nodes.size()+1, theme.node));
					actions.push_back('n');
				} else {
					ConnectionIsActive = false;
					connections.pop_back();
				}
		}
	}
}

void Graph::writeInput () {
	InputWaiting = false;
	connections.back()->setWeight(inputBox.getInput());
}

bool Graph::findNode (Vector2f position, Node **foundNode) {
	for (auto node : nodes)
		if (sqrt(pow(position.x - node->getPosition().x, 2) +
		 	pow(position.y - node->getPosition().y, 2)) <= 
			node->getRadius()) {
			*foundNode = node; 
			return true;
		}
	return false;
}

bool Graph::findConnection (Node* start, Node* end, float* weight) {
	for (auto connection : connections) {
		if (connection->getStartNode() == start && connection->getEndNode() == end) {
			*weight = connection->getWeight();
			return true;
		}
	}
	return false;
}

bool Graph::findConnection (Node* start, Node* end, Connection **foundConnection) {
	for (auto connection : connections) {
		if (connection->getStartNode() == start && connection->getEndNode() == end) {
			*foundConnection = connection;
			return true;
		}
	}
	return false;
}

void Graph::HandleConnection () {
	for (int i = 0; i < connections.size()-1; i++) {
		if (connections[i]->getStartNode() == connections.back()->getStartNode() && 
			connections[i]->getEndNode() == connections.back()->getEndNode()) {
			connections.pop_back();
			return;
		}
		if (connections[i]->getStartNode() == connections.back()->getEndNode() && 
			connections[i]->getEndNode() == connections.back()->getStartNode()) {
			connections.back()->setWeight(connections[i]->getWeight());
			return;
		}
	}
	InputWaiting = true;
	window.setActive(false);
	inputBox.create();
}

void Graph::FindPath () {
	int N = nodes.size();
	int start = startNode->getIndex()-1;
	int end = endNode->getIndex()-1;

	bool *taken = new bool[N];
	float *length = new float[N];
	int *source = new int[N];
	for (int i = 0; i < N; i++) {
		taken[i] = false;
		length[i] = -1;
	}
	taken[start] = true;
	length[start] = 0;
	source[start] = -1;
	int current = start;
	float weight;
	bool found = true;

	while (found) {
		for (int i = 0; i < N; i++) {
			if (!taken[i] && findConnection(nodes[current], nodes[i], &weight)) {
				if (weight + length[current] < length[i] || length[i] == -1) {
					length[i] = weight + length[current];
					source[i] = current;
				}
			}
		}
		float min_length = -1;
		int min_node;
		found = false;
		for (int i = 0; i < N; i++) {
			if (!taken[i] && length[i] != -1) {
				if (length[i] < min_length || !found) {
					min_length = length[i];
					min_node = i;
					found = true;
				}
			}
		}
		if (found) {
			current = min_node;
			taken[current] = true;
		}
	}

	for (auto &node : nodePath) 
		node->setSelected(false);
	for (auto &connection : connectionPath)
		connection->setHighlighted(false);
	connectionPath.clear();
	nodePath.clear();

	Connection* bufferConnection;
	if (length[end] != -1) {
		int next = end;
		while (source[next] != -1) {
			if(findConnection(nodes[source[next]], nodes[next], &bufferConnection))
				connectionPath.push_back(bufferConnection);
			next = source[next];
		}
		next = end;
		while (next != start) {
			nodePath.push_back(nodes[next]);
			next = source[next];
		}
	}
	for (auto &node : nodePath) 
		node->setSelected(true);
	for (auto &connection : connectionPath)
		connection->setHighlighted(true);

}
