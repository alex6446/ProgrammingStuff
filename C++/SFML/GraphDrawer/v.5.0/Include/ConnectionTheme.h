#pragma once

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

typedef struct {

	string 	name;
	Color 	activeColor;
	Color 	finalColor;
	Color 	highlightColor;
	int 	arrowSize;
	Font	font;
	Color 	textColor;
	Color 	highlightTextColor;
	int 	textSize;

} ConnectionTheme;
