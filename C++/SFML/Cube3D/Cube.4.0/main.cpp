#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <SFML/Graphics.hpp>

#include "Camera.h"
#include "Object3D.h"
#include "Scene.h"
#include "Cube3D.h"

using namespace std;
using namespace sf;

#define PI 3.14159265

int main() 
{
    RenderWindow window(VideoMode::getDesktopMode(), "Cube 3.0");
    window.setPosition(Vector2i(
	VideoMode::getDesktopMode().width/2 - window.getSize().x/2,
	VideoMode::getDesktopMode().height/2 - window.getSize().y/2));
	window.setFramerateLimit(60);
	window.setMouseCursorVisible(false);

	Scene scene(window);
	scene.addCamera(new Camera(Vector3f(0.f, 0.f, -5.f), 0.1f));
	scene.addCamera(new Camera(Vector3f(0.976187, 2, 0.72065)));

	Cube3D cube;

	scene.addObject(&cube);
/*	scene.addObject(new Cube3D(Vector3f(-120.f, 0.f, 40.f), 20));
	scene.addObject(new Cube3D(Vector3f(-120.f, 0.f, 80.f), 20));
	scene.addObject(new Cube3D(Vector3f(-60.f, 0.f, 40.f), 20));
	scene.addObject(new Cube3D(Vector3f(-60.f, 0.f, 80.f), 20));*/
	/*scene.addObject(new Cube3D(Vector3f(3.f, 0.f, 0.f)));
	scene.addObject(new Cube3D(Vector3f(-3.f, 0.f, 0.f)));
	scene.addObject(new Cube3D(Vector3f(0.f, 3.f, 0.f)));
	scene.addObject(new Cube3D(Vector3f(0.f, -3.f, 0.f)));
	scene.addObject(new Cube3D(Vector3f(0.f, 0.f, 3.f)));
	scene.addObject(new Cube3D(Vector3f(0.f, 0.f, -3.f)));

	scene.addObject(new Cube3D(Vector3f(6.f, 0.f, 0.f)));
	scene.addObject(new Cube3D(Vector3f(6.f, 2.f, 0.f)));
	scene.addObject(new Cube3D(Vector3f(8.f, 2.f, 0.f)));
	scene.addObject(new Cube3D(Vector3f(8.f, 0.f, 0.f)));*/

	scene.setCamera(0);

    while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed)
				if (event.key.code == Keyboard::Escape)
					window.close();
		}
		
		//cube.move(Vector3f(0.f, 0.f, 0.01f));
		//cube.rotate(Vector3f(0.f, 0.f, 0.5f));
		//cube.rotate(Vector2f(0.5f, 0.f), Vector3f(0.f, 0.f, 3.f));
		scene.update();

		window.clear(Color(0,0,0));
		scene.draw();
		window.display();
	}
}
