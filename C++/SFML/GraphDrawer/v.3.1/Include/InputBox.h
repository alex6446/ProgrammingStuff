#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class InputBox {
private:

	RenderWindow 	window;
	Font 			font;
	Text 			text;
	string 			input;
	Color 			background;

public:

			InputBox ();
	void 	create (string title="Input");
	void 	close ();
	bool 	isActive ();
	string	getInput ();
	void 	setFont (Font &font);
	void 	setTextSize (int size);
	void 	setTextColor (Color &color);
	void 	setBackgroundColor (Color &color);

	void 	update ();
	void 	draw ();

private:

	void 	update_text ();

};
