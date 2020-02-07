#include "InputBox.h"

InputBox::InputBox () {
	font.loadFromFile("Fonts/Terminus-Bold.ttf");
	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(Color(239, 61, 89));
	background = Color(42, 54, 59);
};

void InputBox::create (string title) {
	window.create(VideoMode(180, 80), title, Style::None);
	window.setPosition(Vector2i(VideoMode::getDesktopMode().width/2 - window.getSize().x/2, 
				   				VideoMode::getDesktopMode().height/2 - window.getSize().y/2));
	input = "0";
	update_text();
}

void InputBox::close () {
	window.close();
}

bool InputBox::isActive () { 
	return window.isOpen(); 
}

string InputBox::getInput () {
	return input;
}

void InputBox::setFont (Font &font) {
	this->font = font;
	text.setFont(font);
}

void InputBox::setTextSize (int size) {
	text.setCharacterSize(size);
}

void InputBox::setTextColor (Color &color) {
	text.setFillColor(color);
}

void InputBox::setBackgroundColor (Color &color) {
	background = color;
}


void InputBox::update () {
	if (window.isOpen()) {
		Event event;
		while(window.pollEvent(event)) {
			if (event.type == Event::Closed)
				close();
			if (event.type == Event::TextEntered) {
				if(event.text.unicode > 31) {
					if (input == "0") input.clear();
					input += event.text.unicode;
					update_text();
				}
			} else
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Backspace)
					if (input.size()) {
						input.erase(input.size()-1);
						update_text();
					} 
				if (event.key.code == Keyboard::Enter)
					close();
			}
		}
	}
}

void InputBox::draw () {
	if (window.isOpen()) {
		window.clear(background);
		window.draw(text);
		window.display();
	}
}

void InputBox::update_text () {
	text.setString(input);
	text.setPosition(
		window.getSize().x/2 - text.getLocalBounds().width/2, 
		window.getSize().y/2 - text.getLocalBounds().height/2
	);
}
