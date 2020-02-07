#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "InputBoxTheme.h"

using namespace std;
using namespace sf;

class InputBox {
private:

	RenderWindow 	window;
	Font 			font;
	Text 			text;
	string 			input;

	InputBoxTheme*	theme;

public:
			InputBox ();
			InputBox (InputBoxTheme &theme);
	void 	create (string title="Input");
	void 	close ();
	bool 	isActive ();
	string	getInput ();
	void 	setTheme (InputBoxTheme &theme);

	void 	update ();
	void 	draw ();

private:

	void 	update_text ();

};
