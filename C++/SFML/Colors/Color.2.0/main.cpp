#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using namespace sf;

class Block {
public:
	Image image;
	Texture texture;
	Sprite sprite;

	int width;
	int height;

	Block () {};
	Block (string path) {
		image.loadFromFile(path);
		update();
	}
	Block (int width, int height, Color color) {
		image.create(width, height, color);
		update();
	}

	void normalize (RenderWindow &window) {
		Vector2f screen = Vector2f(window.getSize());
		if (width-(float)screen.x > height-(float)screen.y)
			sprite.setScale((float)screen.x/width, (float)screen.x/width);
		else
			sprite.setScale((float)screen.y/height, (float)screen.y/height);
		sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);
		sprite.setPosition(Vector2f(screen.x, screen.y)/2.f);
	} 

	void update () {
		width = image.getSize().x;
		height = image.getSize().y;
		texture.loadFromImage(image);
		sprite.setTexture(texture);
	}

	void draw (RenderWindow &window) {
		window.draw(sprite);
	}
};

float getHue (Color color) {
	float hue;
	float R = color.r/255;
	float G = color.g/255;
	float B = color.b/255;
	float min = std::min({R, G, B});
	float max = std::max({R, G, B});

	if (R == max) hue = (G-B)/(max-min);
	else if (G == max) hue = 2.0 + (B-R)/(max-min);
	else hue = 4.0 + (R-G)/(max-min);

	hue *= 60;
	if (hue < 0) hue += 360;

	return hue;
}

void QuickSort (vector<Color> &arr, int l, int r) {
	int i = l;
	int j = r;
	float middle = getHue(arr[(i+j)/2]);

	do {

		while (middle > getHue(arr[i])) i++;
		while (middle < getHue(arr[j])) j--;

		if (i <= j) {
			swap(arr[i], arr[j]);
			i++;
			j--;
		}

	} while (i < j);

	if (i < r) QuickSort(arr, i, r);
	if (j > l) QuickSort(arr, l, j);

}

int main () {

	/*int number;
	cout << "Enter ammount of colors: ";
	cin >> number;*/

	Block source("2.jpg");
	Block output(source.width, source.height, Color::Red);
	vector<Block *> blocks;
	vector<Color> colors;

	RenderWindow window(VideoMode(800, 800), "Domain Colors");
	source.normalize(window);

	for (int y = 0; y < source.height; y++)
		for (int x = 0; x < source.width; x++)
			colors.push_back(source.image.getPixel(x, y));

	QuickSort(colors, 0, colors.size()-1);

	for (int y = 0, i = 0; y < output.height; y++)
		for (int x = 0; x < output.width; x++, i++)
			output.image.setPixel(x, y, colors[i]);

	output.update();
	output.normalize(window);



	while (window.isOpen()) {

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear();
		output.draw(window);
		//source.draw(window);
		window.display();
	}


	return 0;
}
