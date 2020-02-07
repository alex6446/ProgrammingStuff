#include "Graph.h"

Graph::Graph () { 
	InputWaiting = false;
	ConnectionIsActive = false;
	window.create(VideoMode::getDesktopMode(), "Graph Drawer");
	LoadThemes();
	setTheme("Default");
}

Graph::Graph (int width, int height, string title) {
	InputWaiting = false;
	ConnectionIsActive = false;
	window.create(VideoMode(width, height), title);
	window.setPosition(Vector2i(
		VideoMode::getDesktopMode().width/2 - window.getSize().x/2,
		VideoMode::getDesktopMode().height/2 - window.getSize().y/2));
	LoadThemes();
	setTheme("Default");
};

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
			/*if (event.key.code == Keyboard::Z)
				if (!PointActive && !edges.empty())
					edges.pop_back();
			if (event.key.code == Keyboard::X)
				if (!PointActive && !edges.empty())
					edges.clear();*/
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

void Graph::click (Vector2f mouse_position) {
	if (!inputBox.isActive()) {
		Node* selectedNode;
		bool NodeHit = findNode(mouse_position, &selectedNode);
		if (NodeHit) {
			if (!ConnectionIsActive) {
				ConnectionIsActive = true;
				connections.push_back(new Connection(selectedNode, theme.connection));
			} else {
				ConnectionIsActive = false;
				connections.back()->setEndNode(selectedNode);
				HandleConnection();
			}
		} else {
			if (!ConnectionIsActive) {
				nodes.push_back(new Node(mouse_position, nodes.size()+1, theme.node));
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
