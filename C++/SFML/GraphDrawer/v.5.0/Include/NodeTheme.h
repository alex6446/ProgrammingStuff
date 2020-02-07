#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

typedef struct {

	string 	name;
	Color 	pointColor;
	Color 	selectedColor;
	int 	pointSize;
	Font 	font;
	Color 	textColor;
	Color 	selectedTextColor;
	int 	textSize;

} NodeTheme;