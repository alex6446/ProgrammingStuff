#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "Node.h"
#include "Connection.h"
#include "InputBox.h"
#include "Net.h"


using namespace std;
using namespace sf;

/*
COLORS

 ARROW ACTIVE 	F26627  (242, 102, 39)  
  				F9A26C (249, 162, 108)
 ARROW SET 		EFEEEE (239, 238, 238)  
 NODES 			9BD7D1 (155, 215, 209)
 BACKGROUND 	325D79 (50, 93, 121)

---------------------------------------

  EF3D59   
  E17A47   
  EFC958   
  NODES 		4AB19D (74, 177, 157)
  BACKGROUND	344E5C (52, 78, 92)
*/

int main () {

	RenderWindow window(VideoMode(800, 520), "Arrows");
	window.setPosition(Vector2i(
	VideoMode::getDesktopMode().width/2 - window.getSize().x/2,
	VideoMode::getDesktopMode().height/2 - window.getSize().y/2));

	Net net;

	while (window.isOpen()) {
		
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
					net.click(Vector2f(Mouse::getPosition(window)));
				}
			}
		}

		net.update(Vector2f(Mouse::getPosition(window)));

		window.clear(Color(42, 54, 59));
		net.draw(window);
		window.display();
	}

}
