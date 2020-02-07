#include "Net.h"

Net::Net () { 
	ConnectionIsActive = false; 
}

/*Net::~Net () {
	for (auto &node : nodes) delete node;
	for (auto &connection : connections) delete connection;
}*/

void Net::click (Vector2f mouse_position) {
	if (!inputBox.isActive()) {
		Node* selectedNode;
		bool NodeHit = findNode(mouse_position, &selectedNode);
		if (NodeHit) {
			if (!ConnectionIsActive) {
				ConnectionIsActive = true;
				connections.push_back(new Connection(selectedNode));
			} else {
				ConnectionIsActive = false;
				connections.back()->setEndNode(selectedNode);
				HandleConnection();
			}
		} else {
			if (!ConnectionIsActive) {
				nodes.push_back(new Node(mouse_position, nodes.size()+1));
			} else {
				ConnectionIsActive = false;
				connections.pop_back();
			}
		}
	}
}

void Net::update (Vector2f mouse_position) {
	if (ConnectionIsActive) {
		connections.back()->setEndPosition(mouse_position);
	}
	inputBox.update();
}

void Net::draw (RenderWindow &window) {
	for (auto connection : connections) connection->draw(window);
	for (auto node : nodes) node->draw(window);
	inputBox.draw();
}

bool Net::findNode (Vector2f position, Node **foundNode) {
	for (auto node : nodes)
		if (sqrt(pow(position.x - node->getPosition().x, 2) +
		 	pow(position.y - node->getPosition().y, 2)) <= 
			node->getRadius()) {
			*foundNode = node; 
			return true;
		}
	return false;
}

void Net::HandleConnection () {
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
	inputBox.inputWeight(connections.back());
}
