#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>

#define PI 3.14159265

using namespace std;
using namespace sf;

void shuffle_array(float *arr, int size) {

	for (int i = 0; i < size; i++) {
		int index = rand() % size;
		swap(arr[i], arr[index]);
	}

}

string conv_to_str (double value) {
		string str = to_string(value);
		while (str.back() == '0')
			str.pop_back();
		if (str.back() == '.')
			str.pop_back();
		return str;
	}

enum class State { main, selected, highlighted };

struct Element {

	float length;
	float angle;
	State state;
	Vertex line[2];
	CircleShape dot;
	Text number;

};

class SortGraph {
private:

	float minLength;
	float maxLength;
	float angle_start;
	float angle_current;
	float angle_step;
	Color main_color;
	Color selected_color;
	Color highlighted_color;
	Vector2f center;
	Font font;
	Element temp;
	vector<Element> elements;
	RenderWindow* window;

public:

	SortGraph (RenderWindow* current_window) {

		window = current_window;
		minLength = 50.f;
		maxLength = min(window->getSize().x, window->getSize().y) / 2 - 10.f;
		angle_start = 45.f;
		main_color = Color(255, 140, 0, 255);
		highlighted_color = Color::Yellow;
		selected_color = Color::Red;
		center = Vector2f(window->getSize().x, window->getSize().y) / 2.f;
		temp.dot.setRadius(3.f);
		temp.dot.setOrigin(Vector2f(temp.dot.getRadius(), temp.dot.getRadius()));
		temp.dot.setFillColor(main_color);
		font.loadFromFile("Roboto-Regular.ttf");
		temp.number.setFont(font);
		temp.number.setCharacterSize(12);

	}

	void update (const float arr[], int N, int ind, bool changed) {

		Color temp_color = main_color;

		angle_current = angle_start;
		//angle_step = 360.f / N * 2 + 3.5; // 3.6 for 100 // 3.5 for 200
		angle_step = 360.f / N;
		elements.clear();
		float x;
		float y;
		float length_k = (maxLength - minLength) / *max_element(arr, arr+N);
		for (int i = 0; i < N; i++) {
			temp.length = arr[i] * length_k + minLength;
			temp.angle = angle_current;
			temp.state = State::main;
			if (i == ind) {
				if (changed) {
					temp.state = State::selected;
					temp_color = selected_color;
					temp.number.setFillColor(selected_color);
				} else {
					temp.state = State::highlighted;
					temp_color = highlighted_color;
					temp.number.setFillColor(highlighted_color);
				}
			} else {
				temp.number.setFillColor(Color::White);
			}
			x = cos(temp.angle / 180 * PI) * temp.length;
			y = sin(temp.angle / 180 * PI) * temp.length;
			x += center.x;
			y = center.y - y;
			temp.line[0] = Vertex(center, temp_color);
			temp.line[1] = Vertex(Vector2f(x, y), temp_color);
			temp.dot.setPosition(temp.line[1].position);
			temp.dot.setFillColor(temp_color);
			temp.number.setString(conv_to_str(arr[i]));
			temp.number.setOrigin(Vector2f(0, temp.number.getLocalBounds().height));
			temp.number.setPosition(int(temp.line[1].position.x + 5), int(temp.line[1].position.y - 5));
			elements.push_back(temp);
			angle_current -= angle_step;
			temp_color = main_color;
		}

	}

	void draw () {

		for (int i = 0; i < elements.size(); i++)
			window->draw(elements[i].line, 2, Lines);
		for (int i = 0; i < elements.size(); i++)
			window->draw(elements[i].dot);
		for (int i = 0; i < elements.size(); i++)
			window->draw(elements[i].number);

	}

};

int main () {

	RenderWindow window(VideoMode(1280, 968, 32), "Graphical Sorting");

	SortGraph bubble(&window);

	int N = 360; // 100
	float *arr = new float[N];

	srand(time(NULL));

	for (int i = 0; i < N; i++) {
		arr[i] = rand();
		//arr[i] = i+1;
	}

	//shuffle_array(arr, N);

	/*for (int i = N - 1; i > 0; i--)
		for (int j = 0; j < i; j++)
			if (arr[j] > arr[j+1])
				swap(arr[j], arr[j+1]);*/

	int max_wait = 0;
	int wait = 0;
	int bi = N-1;
	int bj = 0;
	bool changed = false;

	while (window.isOpen()) {

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}

		if (wait >= max_wait) {
			if (bi > 0) {
				if (bj < bi) {
					if (arr[bj] > arr[bj+1]){
						swap(arr[bj], arr[bj+1]);
						changed = true;
					} else {
						changed = false;
					}
					bj++;
				} else {
					bj = 0;
					bi--;
				}
			} else {
				bj = -1;
			}
			wait = 0;
		} else {
			wait++;
		}

		bubble.update(arr, N, bj, changed);
		window.clear(Color(32, 35, 43, 255));
		/*window.draw(center);
		window.draw(dot);
		window.draw(line, 2, Lines);
		window.draw(number);*/
		bubble.draw();
		window.display();

	}

	return 0;
}
