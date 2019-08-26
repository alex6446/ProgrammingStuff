#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace sf;

char Player;
char GameState; // Menu / Game / Result
char Winner;
char** Field;

Font font;
Text textWinner;
Text textSadSmile;

vector<RectangleShape> Xcords;
vector<CircleShape> Ocords;

CircleShape O;
RectangleShape X;

bool MouseLeftButtonPressed;

char CheckWin() {
	int count1 = 0;
	int count2 = 0;
	int count3 = 0;
	int count4 = 0;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (Field[i][j] == 'X')
				count1++;
			if (Field[i][j] == 'O')
				count2++;
			if (Field[j][i] == 'X')
				count3++;
			if (Field[j][i] == 'O')
				count4++;
		}
		if (count1 == 3 || count3 == 3)
			return 'X';
		if (count2 == 3 || count4 == 3)
			return 'O';
		count1 = 0;
		count2 = 0;
		count3 = 0;
		count4 = 0;
	}

	for (int i = 0; i < 3; i++) {
		if (Field[i][i] == 'X')
			count1++;
		else if (Field[i][i] == 'O')
			count2++;
		if (Field[i][3-i-1] == 'X')
			count3++;
		else if (Field[i][3-i-1] == 'O')
			count4++;
		}

	if (count1 == 3 || count3 == 3)
		return 'X';
	if (count2 == 3 || count4 == 3)
		return 'O';

	return '*';
}

bool Is_full() {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (Field[i][j] != 'X' && Field[i][j] != 'O')
				return false;
	return true;
}

int main () {
	
	RenderWindow window(VideoMode(320, 400), "Tic Tac Toe"); //380 460
	window.setFramerateLimit(25);

	////////////////////////// GAMEPLAY VARIABLES //////////////////////////
	
	Player = 'X';
	GameState = 'M';
	Winner = '*';

	Field = new char*[3];
	for (int i = 0; i < 3; i++)
		Field[i] = new char[3];

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			Field[i][j] = '*';

	Vector2f CenterCords [3][3] = {
		Vector2f(65.f, 145.f), Vector2f(160.f, 145.f), Vector2f(255.f, 145.f),
		Vector2f(65.f, 240.f), Vector2f(160.f, 240.f), Vector2f(255.f, 240.f),
		Vector2f(65.f, 335.f), Vector2f(160.f, 335.f), Vector2f(255.f, 335.f)
	};

	
	font.loadFromFile("Roboto-Regular.ttf");

	textWinner.setFont(font);
	textWinner.setCharacterSize(28);
	textWinner.setString(L"Ошибка!");
	textWinner.setOrigin(textWinner.getLocalBounds().width/2, 
						 textWinner.getLocalBounds().height/2);
	textWinner.setPosition(Vector2f(window.getSize().x/2, 240.f));

	textSadSmile.setFont(font);
	textSadSmile.setCharacterSize(50);
	textSadSmile.setString(":(");
	textSadSmile.setOrigin(textSadSmile.getLocalBounds().width/2, 
						   textSadSmile.getLocalBounds().height/2);
	textSadSmile.setPosition(Vector2f(window.getSize().x/2, 170.f));

	//////////////////////////// DRAW MENU //////////////////////////////////

	RectangleShape ResultBackground((Vector2f)window.getSize());
	ResultBackground.setFillColor(Color(0, 0 ,0 ,230));

	//////////////////////////// DRAW BORDERS ///////////////////////////////

	Vector2f line_h = Vector2f(280.f, 5.f);
	Vector2f line_v = Vector2f(5.f, 280.f);
 	
	RectangleShape h1(line_h);
	RectangleShape h2(line_h);
	RectangleShape v1(line_v);
	RectangleShape v2(line_v);
	h1.setPosition(Vector2f(20.f, 190.f));
	h2.setPosition(Vector2f(20.f, 285.f));
	v1.setPosition(Vector2f(110.f, 100.f));
	v2.setPosition(Vector2f(205.f, 100.f));

	//////////////////////////// X AND O SETUP ////////////////////////////

	O.setRadius(28.f);
	O.setFillColor(Color::Black);
	O.setOutlineThickness(5.f);
	O.setOrigin(Vector2f(O.getRadius(), O.getRadius()));

	X.setSize(Vector2f(80.f, 5.f));
	X.setOrigin(X.getSize()/2.f);
	X.setRotation(45.f);

	/////////////////////////////// MAIN LOOP /////////////////////////////////////
	
	while (window.isOpen()) {

		MouseLeftButtonPressed = false;
	
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Escape)
					window.close();
			}
			if (event.type == Event::MouseButtonPressed) {
				if (event.mouseButton.button == Mouse::Left){
					cout << "Pressed" << endl;
					MouseLeftButtonPressed = true;
				}
			}
		}

		////////////////////////// UPDATE ///////////////////////////

		if (GameState == 'M') {
			if (MouseLeftButtonPressed) {
				Player = 'X';
				GameState = 'G';
				Winner = '*';
				for (int i = 0; i < 3; i++)
					for (int j = 0; j < 3; j++)
						Field[i][j] = '*';
				Xcords.clear();
				Ocords.clear();
				textWinner.setString(L"Ошибка!");
				textWinner.setOrigin(textWinner.getLocalBounds().width/2, 
									 textWinner.getLocalBounds().height/2);
				MouseLeftButtonPressed = false;
			}
		}

		if (GameState == 'G') {
			if (MouseLeftButtonPressed) {
				for (int i = 0; i < 3; i++) 
					for (int j = 0; j < 3; j++) {
						if (Mouse::getPosition(window).x > (CenterCords[i][j].x - 45.f) &&
						 	Mouse::getPosition(window).y > (CenterCords[i][j].y - 45.f) &&
							Mouse::getPosition(window).x < (CenterCords[i][j].x + 45.f) &&
							Mouse::getPosition(window).y < (CenterCords[i][j].y + 45.f)	 )
							if (Field[i][j] == '*') 
								if (Player == 'X') {
									Field[i][j] = 'X';
									X.setPosition(CenterCords[i][j]);
									Xcords.push_back(X);
									X.setRotation(X.getRotation()*-1);
									Xcords.push_back(X);
									Player = 'O';
								} else if (Player == 'O') {
									Field[i][j] = 'O';
									O.setPosition(CenterCords[i][j]);
									Ocords.push_back(O);
									Player = 'X';
								}
				 	}
				 MouseLeftButtonPressed = false;
			}
			if (CheckWin() == 'X') {
				Winner = 'X';
				GameState = 'R';
			} else if (CheckWin() == 'O') {
				Winner = 'O';
				GameState = 'R';
			} else if (Is_full()) 
				GameState = 'R';
		}

		if (GameState == 'R') {
			if (Winner == '*')
				textWinner.setString(L"Ничья!");
			else if (Winner == 'X') {
				textWinner.setString(L"ПОБЕДИЛ!");
				X.setPosition(Vector2f(window.getSize().x/2, 180.f));
			}
			else if (Winner == 'O') {
				textWinner.setString(L"ПОБЕДИЛ!");
				O.setPosition(Vector2f(window.getSize().x/2, 180.f));
			}
			textWinner.setOrigin(textWinner.getLocalBounds().width/2, 
						 		 textWinner.getLocalBounds().height/2);
			if (MouseLeftButtonPressed) {
				GameState = 'M';
			}
		}

		////////////////////////// DRAW //////////////////////////////

		window.clear();

		if (GameState == 'G') {
			window.draw(h1);
			window.draw(h2);
			window.draw(v1);
			window.draw(v2);

			for (int i = 0; i < Xcords.size(); i++)
				window.draw(Xcords[i]);
			for (int i = 0; i < Ocords.size(); i++)
				window.draw(Ocords[i]);
		}
		if (GameState == 'R') {
			
			window.draw(h1);
			window.draw(h2);
			window.draw(v1);
			window.draw(v2);

			for (int i = 0; i < Xcords.size(); i++)
				window.draw(Xcords[i]);
			for (int i = 0; i < Ocords.size(); i++)
				window.draw(Ocords[i]);

			window.draw(ResultBackground);

			if (Winner == 'X') {
				window.draw(X);
				X.setRotation(X.getRotation()*-1);
				window.draw(X);
			} else if (Winner == 'O') {
				O.setFillColor(Color(0, 0 ,0 ,0));
				window.draw(O);
				O.setFillColor(Color(0, 0 ,0 ,255));
			} else if (Winner == '*')
				window.draw(textSadSmile);
			window.draw(textWinner);
		}

		window.display();
	}

	return 0;
}
