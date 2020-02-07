#pragma once

#include "NodeTheme.h"
#include "ConnectionTheme.h"
#include "InputBoxTheme.h"

using namespace std;
using namespace sf;

typedef struct {

	string 				name;
	Color				backgroundColor;
	NodeTheme 			node;
	ConnectionTheme		connection;
	InputBoxTheme		ibox;

} Theme;
