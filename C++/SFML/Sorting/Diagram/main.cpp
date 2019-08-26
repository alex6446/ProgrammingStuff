#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <vector>

using namespace std;
using namespace sf;

void shuffle_array(int *arr, int size) {

	for (int i = 0; i < size; i++) {
		int index = rand() % size;
		swap(arr[i], arr[index]);
	}

}

int main() {
	
	srand(time(NULL));

	int size = 30;
	cout << "Enter amount of elements: " << endl;
	cin >> size;

	int *array = new int[size];
	for (int i = 0; i < size; i++)
		array[i] = i+1;

	shuffle_array(array, size);

	RenderWindow window(VideoMode(1080, 640), "BubbleSort!");
    	
	RectangleShape element;

	float width = window.getSize().x / (float)size;
	float height_k = window.getSize().y / (float)size;
	vector<RectangleShape> elements;
	
	float pos_x = 0;

	for (int i = 0; i < size; i++) {
		element.setSize(Vector2f(width, array[i] * height_k));
		element.setPosition(pos_x, window.getSize().y - element.getSize().y);
		elements.push_back(element);
		pos_x += width;
	}

	elements.back().setFillColor(Color::Red);

    while (window.isOpen()) {

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		
		window.clear();
		//window.draw(shape);
		for (int i = 0; i < elements.size(); i++) {
			window.draw(elements[i]);	
		}
		window.display();
    }

	return 0;
}
