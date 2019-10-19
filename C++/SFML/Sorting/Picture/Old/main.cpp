#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include<ctime>

using namespace std;
using namespace sf;

int main () {

	//srand(time(NULL));

	Image sourceImg;
	Texture sourceTexture;
	Sprite sourceSprite;

	sourceImg.loadFromFile("source.jpg");

	int width = sourceImg.getSize().x;
	int height = sourceImg.getSize().y;
	int cellSize = 128;
	int cellWidth = width / cellSize;
	int cellHeight = height / cellSize;
	int cellNumber = cellHeight * cellWidth;

	RenderWindow window(VideoMode(width, height), "Picture Sorting");
	window.setFramerateLimit(60);

	Sprite* sprite = new Sprite[cellNumber];
	Texture* texture = new Texture[cellNumber];
	Image* image = new Image[cellNumber];
	int* index = new int[cellNumber];
	Vector2f* positions = new Vector2f[cellNumber];

	int ind = 0;
	for (int i = 0; i < height; i += cellSize) {
		for (int j = 0; j < width; j += cellSize) {
			image[ind].create(cellSize, cellSize);
			index[ind] = ind;
			for (int k = 1; k < cellSize; k++) {
				for (int l = 1; l < cellSize; l++) {
					image[ind].setPixel(k, l, sourceImg.getPixel(k+j, l+i));
				}
			}
			texture[ind].loadFromImage(image[ind]);
			sprite[ind].setTexture(texture[ind]);
			positions[ind] = Vector2f(j, i);
			ind++;
		}
	}

	for (int i = 0; i < cellNumber; i++) {
		ind = rand() % cellNumber;
		swap(index[i], index[ind]);
		swap(sprite[i], sprite[ind]);
	}

	int max_wait = 0;
	int wait = 0;
	int bi = cellNumber-1;
	int bj = 0;

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Escape)
					window.close();
			}
		}

		if (wait >= max_wait) {
			if (bi > 0) {
				if (bj < bi) {
					if (index[bj] > index[bj+1]) {
						swap(index[bj], index[bj+1]);
						swap(sprite[bj], sprite[bj+1]);
					}
					bj++;
				} else {
					bj = 0;
					bi--;
				}
			} else {
				bj = -1;
			}
			wait = 0;
		} else {
			wait++;
		}

		sourceTexture.loadFromImage(sourceImg);
		sourceSprite.setTexture(sourceTexture);

		window.clear();
		for (int i = 0; i < cellNumber; i++) {
			sprite[i].setPosition(positions[i]);
			window.draw(sprite[i]);
		}
		window.display();
	}

	return 0;
}