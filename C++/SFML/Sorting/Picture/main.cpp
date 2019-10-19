#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include<ctime>

using namespace std;
using namespace sf;

class Sort {
private:

	Image sourceImage;
	Texture sourceTexture;
	Sprite sourceSprite;
	Vector2f* elementPositions;
	Image* elementImage;
	Texture* elementTexture;
	Sprite* elementSprite;
	int* elementIndex;
	int width;
	int height;
	int cellSize;
	int cellWidth; 
	int cellHeight;
	int cellNumber;

	enum Modes {BubbleSort = 1, SelectionSort, QuickSort, InsertionSort};
	Modes mode;

	struct SortVariables {
		vector<int> buffer_l;
		vector<int> buffer_r;
		bool next;
		bool i_set;
		bool j_set;
		int l;
		int r;
		int i;
		int j;
		int middle;
		int min;
	};
	SortVariables var;

public:

	Sort () {
		sourceImage.loadFromFile("source.jpg");
		width = sourceImage.getSize().x;
		height = sourceImage.getSize().y;
		setup();
	}

	VideoMode getVideoMode () {
		return VideoMode(width, height);
	}

	void update () {
		switch (mode) {
			case 1:
				if (var.i > 0) {
					if (var.j < var.i) {
						if (elementIndex[var.j] > elementIndex[var.j+1]) {
							swap_cell(var.j, var.j+1);
						}
						var.j++;
					} else {
						var.j = 0;
						var.i--;
					}
				} else {
					var.j = -1;
				}
				break;
			case 2:
				if (var.i < cellNumber-1) {
					if (var.j == var.i+1) {
						var.min = var.i;
					}
					if (var.j < cellNumber) {
						if (elementIndex[var.j] < elementIndex[var.min])
							var.min = var.j;
						var.j++;
					} else {
						swap_cell(var.i, var.min);
						var.i++;
						var.j = var.i+1;
					}

				} else {
					var.j = -1;
				}
				break;
			case 3:
				if (!var.buffer_l.empty() && !var.buffer_r.empty()) {
					if (var.next) {
						var.l = var.buffer_l.back();
						var.r = var.buffer_r.back();
						var.i = var.l;
						var.j = var.r;
						var.middle = elementIndex[(var.i + var.j)/2];
						var.next = false;
					}
					if (var.i <= var.j) {
						if (var.middle > elementIndex[var.i])
							var.i++;
						else
							var.i_set = true;
						if (var.middle < elementIndex[var.j])
							var.j--;
						else
							var.j_set = true;

						if (var.i_set && var.j_set) {
							if (var.i <= var.j) {
								swap_cell(var.i, var.j);
								var.i++;
								var.j--;
							}
							var.i_set = false;
							var.j_set = false;
						}
					} else {
						var.i_set = false;
						var.j_set = false;
						var.next = true;
						var.buffer_l.pop_back();
						var.buffer_r.pop_back();
						if (var.i < var.r) {
							var.buffer_l.push_back(var.i);
							var.buffer_r.push_back(var.r);
						}
						if (var.j > var.l) {
							var.buffer_l.push_back(var.l);
							var.buffer_r.push_back(var.j);
						}
					}
				} 
				break;
			case 4:
				if (var.i < cellNumber) {
					if (var.j > 0) {
						if (elementIndex[var.j] < elementIndex[var.j-1]) {
							swap_cell(var.j, var.j-1);
							var.j--;
						} else {
							var.i++;
							var.j = var.i; 
						}
					} else {
						var.i++;
						var.j = var.i;
					}
				} else {
					var.j = -1;
				}
				break;
		}
	}

	void draw (RenderWindow *window) {
		for (int i = 0; i < cellNumber; i++) {
			elementSprite[i].setPosition(elementPositions[i]);
			window->draw(elementSprite[i]);
		}
	}

private:

	void setup () {

		menu();
		cellWidth = width / cellSize;
		cellHeight = height / cellSize;
		cellNumber = cellHeight * cellWidth;
		elementPositions = new Vector2f[cellNumber];
		elementImage = new Image[cellNumber];
		elementTexture = new Texture[cellNumber];
		elementSprite = new Sprite[cellNumber];
		elementIndex = new int[cellNumber];

		int index = 0;
		for (int i = 0; i < height; i += cellSize) {
			for (int j = 0; j < width; j += cellSize) {
				elementImage[index].create(cellSize, cellSize);
				elementIndex[index] = index;
				for (int k = 1; k < cellSize; k++) {
					for (int l = 1; l < cellSize; l++) {
						elementImage[index].setPixel(k, l, sourceImage.getPixel(k+j, l+i));
					}
				}
				elementTexture[index].loadFromImage(elementImage[index]);
				elementSprite[index].setTexture(elementTexture[index]);
				elementPositions[index] = Vector2f(j, i);
				index++;
			}
		}
		shuffle();
		setup_mode();

	}

	void menu () {

		cout << "Available cell sizes: " << endl;

		vector<int> cellSizes;
		for (int i = 1; i < 300; i++)
			if (!(width % i) && !(height % i)) {
				cellSizes.push_back(i);
				cout << i << endl;
			}

		cout << "Enter cell size: ";
		cin >> cellSize;
		cout << endl;

		cout << "Number of elements: " << width / cellSize * height / cellSize << endl;
		cout << endl; 

		int choice;
		cout << "Available sort modes: " << endl;
		cout << "1. Bubble Sort" << endl;
		cout << "2. Selection Sort" << endl;
		cout << "3. Quick Sort" << endl;
		cout << "4. Insertion Sort" << endl;
		cout << "Enter sort mode: ";
		cin >> choice;
		switch (choice) {
			case 1: mode = Modes::BubbleSort; break;
			case 2: mode = Modes::SelectionSort; break;
			case 3: mode = Modes::QuickSort; break;
			case 4: mode = Modes::InsertionSort; break;
			default: mode = Modes::BubbleSort;
		}

	}

	void shuffle () {
		srand(time(NULL));
		int index;
		for (int i = 0; i < cellNumber; i++) {
			index = rand() % cellNumber;
			swap_cell(i, index);
		}
	}

	void swap_cell (int a, int b) {
		swap(elementIndex[a], elementIndex[b]);
		swap(elementSprite[a], elementSprite[b]);
	}

	void setup_mode () {
		switch (mode) {
			case 1: 
				var.i = cellNumber-1;
				var.j = 0;
				break;
			case 2: 
				var.i = 0;
				var.j = var.i+1;
				var.min = var.i;
				break;
			case 3:
				var.next = true;
				var.i_set = false;
				var.j_set = false;
				var.buffer_l.push_back(0);
				var.buffer_r.push_back(cellNumber-1);
				break;
			case 4: 
				var.i = 1;
				var.j = var.i;
				break;
		}
	}

};

int main() {

	Sort BubbleSort;

	RenderWindow window(BubbleSort.getVideoMode(), "Picture Sorting");
	//window.setFramerateLimit(60);

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Escape)
					window.close();
			}
		}

		BubbleSort.update();

		window.clear();
		BubbleSort.draw(&window);
		window.display();
	}

	return 0;
}