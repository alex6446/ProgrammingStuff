#pragma once

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

typedef struct {

	string 		name;
	VideoMode	windowSize;
	Color 		backgroundColor;
	Font		font;
	Color 		textColor;
	int 		textSize;

} InputBoxTheme;
