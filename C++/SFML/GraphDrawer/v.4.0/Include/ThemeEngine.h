#pragma once

#include "Theme.h"
#include <vector>

void LoadThemes ();

NodeTheme 			GetNodeTheme(string);
ConnectionTheme 	GetConnectionTheme(string);
InputBoxTheme 		GetInputBoxTheme(string);
Theme 				GetTheme(string);

