#include "InputBox.h"

InputBox::InputBox () {};

InputBox::InputBox (InputBoxTheme &theme) {
	setTheme(theme);
};

void InputBox::create (string title) {
	window.create(theme->windowSize, title, Style::None);
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

void InputBox::setTheme (InputBoxTheme& theme) {
	this->theme = &theme;
	text.setFont(theme.font);
	text.setCharacterSize(theme.textSize);
	text.setFillColor(theme.textColor);
	update_text();
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
		window.clear(theme->backgroundColor);
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
