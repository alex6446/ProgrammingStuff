#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class MessageBox {

	static int Input () {
		return 0;
	}

};

int main()
{
    RenderWindow window(VideoMode(800, 520), "Input Box", Style::None);
    window.setPosition(Vector2i(VideoMode::getDesktopMode().width/2 - 
    							window.getSize().x/2, 
    				   			VideoMode::getDesktopMode().height/2 - 
    				   			window.getSize().y/2));
    Font font;
    font.loadFromFile("Terminus-Bold.ttf");

    vector<Text> playerLines;
	string playerInput;
	Text playerText;
	playerText.setFont(font);
	playerText.setCharacterSize(28);
    int lines = 0;
	double k = playerText.getCharacterSize();
	playerText.setFillColor(Color(30, 197, 3));

	while (window.isOpen()) {
		playerText.setPosition(
			window.getSize().x/2 - playerText.getLocalBounds().width/2, 
			window.getSize().y/2 - playerText.getLocalBounds().height/2 + lines*k/2
		);
		Event event;
		while(window.pollEvent(event)) {
			if (event.type == Event::TextEntered) {
				if(event.text.unicode > 31) {
					playerInput += event.text.unicode;
					playerText.setString(playerInput);
				}
			} else
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Backspace)
					if (playerInput.size()) {
						playerInput.erase(playerInput.size()-1);
						playerText.setString(playerInput);
					} else if (!playerLines.empty()) {
						playerText = playerLines.back();
						playerInput = playerText.getString();
						playerLines.pop_back();
						lines--;
						for (auto &line : playerLines) {
							line.setPosition(line.getPosition().x, 
											 line.getPosition().y+k/2);
						}
					} 
				if (event.key.code == Keyboard::Escape) 
					window.close();
				if (event.key.code == Keyboard::Enter) {
					playerLines.push_back(playerText);
					playerInput.clear();
					playerText.setString(playerInput);
					lines++;
					for (auto &line : playerLines) {
						line.setPosition(line.getPosition().x, 
										 line.getPosition().y-k/2);
					}
				}
			}
		}
		window.clear();
		window.draw(playerText);
		for (auto &line : playerLines) {
			window.draw(line);
		}
		window.display();
	}
    return 0;
}
