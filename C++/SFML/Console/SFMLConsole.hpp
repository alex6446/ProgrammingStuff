#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;
using namespace std;

////// USAGE //////

// SFMLConsole console;
// console.print("Variable value: ");
// console.add(variable);
// console.update();


class SFMLConsole {
private:
	RenderWindow console;
	vector<Text> input;
	Font font;
	int fontSize;
public:
	SFMLConsole () {
		console.create(VideoMode(350, 400), "Console");
		font.loadFromFile("Roboto-Regular.ttf");
		fontSize = 24;
	}
	SFMLConsole (int width, int height) {
		console.create(VideoMode(width, width), "SFML Console");
		font.loadFromFile("Roboto-Regular.ttf");
		fontSize = 24;
	}
	// for more inputs use string convertion EX: print((string)"hello"+(string)"world");
	void print (string value) {
		Text text;
		text.setFont(font);
		text.setCharacterSize(fontSize);
		text.setString(value);
		input.push_back(text);
	}
	void print (double value) {
		string str = to_string(value);
		while (str.back() == '0')
			str.pop_back();
		if (str.back() == '.')
			str.pop_back();
		print(str);
	}
	void add (string value) {
		if (input.empty()) {
			print (value);
			return;
		}
		input.back().setString(input.back().getString() + value);
	}
	void add (double value) {
		string str = to_string(value);
		while (str.back() == '0')
			str.pop_back();
		if (str.back() == '.')
			str.pop_back();
		add(str);
	}
	void view () {
		Event event;
		while (console.pollEvent(event)) {
			if (event.type == Event::Closed)
				console.close();
		}
		console.clear();
		float x = 5.f;
		float y = 5.f;
		for (Text line : input) {
			line.setPosition(Vector2f(x, y));
			console.draw(line);
			y += fontSize*1.5;
		}
		console.display();
		input.clear();
	}
};