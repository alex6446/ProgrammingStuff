#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "Connection.h"

using namespace std;
using namespace sf;

class InputBox {
private:

	RenderWindow 	window;
	Font 			font;
	Text 			text;
	string 			input;
	Connection* 	connection;

public:

			InputBox ();
	bool 	isActive ();
	void 	inputWeight (Connection *connection);
	void 	update ();
	void 	draw ();

private:

	void 	update_text ();
	void 	update_weight ();

};
