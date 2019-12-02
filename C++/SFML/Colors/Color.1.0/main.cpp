#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

void QuickSort () {
	return;
}

int main () {

	RenderWindow window(VideoMode(VideoMode::getDesktopMode()), "Domain Color");

	Image in_img;
	Image out_img;
	Texture in_tex;
	Texture out_tex;
	Sprite in_sprite;
	Sprite out_sprite;

	in_img.loadFromFile("in.jpg");
	in_tex.loadFromImage(in_img);
	in_sprite.setTexture(in_tex);

	int width = in_img.getSize().x;
	int height = in_img.getSize().y;

	unsigned long long average_r = 0;
	unsigned long long average_g = 0;
	unsigned long long average_b = 0;

	for (int x = 1; x < width; x++)
		for (int y = 1; y < height; y++) {
			average_r += in_img.getPixel(x, y).r;
			average_g += in_img.getPixel(x, y).g;
			average_b += in_img.getPixel(x, y).b;
		}

	average_r = average_r / (width*height);
	average_g = average_g / (width*height);
	average_b = average_b / (width*height);

	

	out_img.create(width, height, Color(average_r, average_g, average_b, 255));

	/*for (int x = 1; x < width; x++)
		for (int y = 1; y < height; y++)
			out_img.setPixel(x, y, in_img.getPixel(x, y));*/

	out_tex.loadFromImage(out_img);
	out_sprite.setTexture(out_tex);

	while (window.isOpen()) {

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(out_sprite);
		window.display();
	}


	return 0;
}
