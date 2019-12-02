#include "Scene.h"

Scene::Scene (RenderWindow &window) {
	this->window = &window;
}

void Scene::addCamera (Camera *camera) { cameras.push_back(camera); }
void Scene::setCamera (int i) { camera = cameras[i]; }

void Scene::addObject (Object3D *object) {
	object->setWindow(*window);
	objects.push_back(object);
}

void Scene::update () {
	if (Keyboard::isKeyPressed(Keyboard::D))
		camera->move(Sides::Right);
	else if (Keyboard::isKeyPressed(Keyboard::A))
		camera->move(Sides::Left);
	if (Keyboard::isKeyPressed(Keyboard::W))
		camera->move(Sides::Forward);
	else if (Keyboard::isKeyPressed(Keyboard::S))
		camera->move(Sides::Back);
	if (Keyboard::isKeyPressed(Keyboard::Space))
		camera->move(Sides::Up);
	else if (Keyboard::isKeyPressed(Keyboard::LShift))
		camera->move(Sides::Down);
	if (Keyboard::isKeyPressed(Keyboard::Q))
		cout << camera->getPosition().x << ", " 
			 << camera->getPosition().y << ", " << camera->getPosition().z << endl;
	camera->rotate((Vector2f(Mouse::getPosition(*window))- Vector2f(window->getSize())*0.5f)*0.1f);
	Mouse::setPosition(Vector2i(Vector2f(window->getSize())*0.5f), *window);
}

void Scene::draw () {
	for (auto i : objects) 
		i->draw(camera);
}
