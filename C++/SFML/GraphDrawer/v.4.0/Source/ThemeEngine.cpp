#include "ThemeEngine.h"

vector<NodeTheme> NodeThemes;
vector<ConnectionTheme> ConnectionThemes;
vector<InputBoxTheme> InputBoxThemes;
vector<Theme> Themes;


Font TerminusBold;

void ListFonts () {
	TerminusBold.loadFromFile("Fonts/Terminus-Bold.ttf");
};

void ListNodeThemes () {
	NodeThemes.push_back({
		"Default",
		Color::Green, 14,				
		TerminusBold, Color::Black, 18
	});
	NodeThemes.push_back({
		"Sea",
		Color(74, 177, 157), 14,				// Node
		TerminusBold, Color(40, 92, 82), 18		// Text
	});
	NodeThemes.push_back({
		"Azul",
		Color(109, 215, 227), 14,				// Node Color(155, 89, 182) Color(109, 215, 227)
		TerminusBold, Color(26, 122, 103), 18		// Text Color(79, 45, 92) Color(26, 122, 103)
	});
}

void ListConnectionThemes () {
	ConnectionThemes.push_back({
		"Default",
		 Color::Magenta, Color::White, 7, 				// Connection
		 TerminusBold, Color::White, 16					// Text
	});
	ConnectionThemes.push_back({
		"Sea",
		 Color(239, 61, 89), Color(239, 238, 238), 7, 	// Connection
		 TerminusBold, Color(239, 238, 238), 16			// Text
	});
	ConnectionThemes.push_back({
		"Azul",
		 Color(52, 152, 219), Color(64, 98, 130), 7, 	// Connection 
		 TerminusBold, Color(64, 98, 130), 16			// Text
	});
	ConnectionThemes.push_back({
		"AzulLighter",
		 Color(52, 152, 219), Color(75, 113, 148), 7, 	// Connection 
		 TerminusBold, Color(75, 113, 148), 16			// Text
	});
}

void ListInputBoxThemes () {
	InputBoxThemes.push_back({
		"Default",
		VideoMode(180, 80), Color::Black,		// Window
		TerminusBold, Color::White, 24 			// Text
	});
	InputBoxThemes.push_back({
		"Sea",
		VideoMode(180, 80), Color(42, 54, 59),	// Window
		TerminusBold, Color(239, 61, 89), 24 	// Text
	});
	InputBoxThemes.push_back({
		"Azul",
		VideoMode(180, 80), Color(34, 48, 61),	// Window
		TerminusBold, Color(52, 152, 219), 24 	// Text
	});
}

void ListThemes () {
	Themes.push_back({
		"Default",
		Color::Black,
		GetNodeTheme("Default"),
		GetConnectionTheme("Default"),
		GetInputBoxTheme("Default")
	});
	Themes.push_back({
		"Sea",
		Color(42, 54, 59),
		GetNodeTheme("Sea"),
		GetConnectionTheme("Sea"),
		GetInputBoxTheme("Sea")
	});
	Themes.push_back({
		"Azul",
		Color(34, 48, 61),
		GetNodeTheme("Azul"),
		GetConnectionTheme("AzulLighter"),
		GetInputBoxTheme("Azul")
	});
}

void LoadThemes () {
	ListFonts();
	ListNodeThemes();
	ListConnectionThemes();
	ListInputBoxThemes();
	ListThemes();
}


NodeTheme GetNodeTheme (string name) {
	for (auto theme : NodeThemes)
		if (theme.name == name)
			return theme;
	return NodeThemes[0];
}
ConnectionTheme GetConnectionTheme (string name) {
	for (auto theme : ConnectionThemes)
		if (theme.name == name)
			return theme;
	return ConnectionThemes[0];
}
InputBoxTheme GetInputBoxTheme (string name) {
	for (auto theme : InputBoxThemes)
		if (theme.name == name)
			return theme;
	return InputBoxThemes[0];
}
Theme GetTheme (string name) {
	for (auto theme : Themes) 
		if (theme.name == name)
			return theme;
	return Themes[0];
}

