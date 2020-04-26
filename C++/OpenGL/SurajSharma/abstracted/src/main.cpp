#include "Game.h"

int main () {

	Game game(
		"GL App", 
		1920, 1080,
		4, 5,
		true 
	);

	//MAIN LOOP
	while (!game.getWindowShouldClose()) {

		game.update();
		game.render();
		//updateInput(window, mesh);

		//UPDATE
		//updateInput(window);
	}

	return 0;
} 
