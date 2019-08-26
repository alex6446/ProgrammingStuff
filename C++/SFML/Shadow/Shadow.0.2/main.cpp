#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>

#define PI 3.14159265

using namespace sf;
using namespace std;

class TileMap {
private:
	
	int size;
	int width;
	int height;
	bool **map;
	Color color;
	vector<RectangleShape> tiles;
	vector<Vector2f> vertices;
	vector<vector<Vector2f>> edges;

public:
	
	TileMap () 
	{ setup(25, 26, 18, Color::Blue); }

	TileMap (int setup_size, int setup_width, int setup_height, Color setup_color) 
	{ setup(setup_size, setup_width, setup_height, setup_color); }

private:

	void setup (int setup_size, int setup_width, int setup_height, Color setup_color) {
		size = setup_size;
		width = setup_width;
		height = setup_height;
		color = setup_color;
		map = new bool*[width];
		for (int i = 0; i < width; i++) {
			map[i] = new bool[height];
			for (int j = 0; j < height; j++)
				map[i][j] = false;
		}
	}

	void update () { 
		
		vector<Vector2f> buffer_top;
		vector<Vector2f> buffer_bottom;
		bool top_active = false;
		bool bottom_active = false;

		vertices.clear();
		edges.clear();

		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				if (map[i][j]) {
					if (i != 0) {
						if (!map[i-1][j]) {
							if (!top_active) {
								top_active = true;
								vertices.push_back(Vector2f(i*size, j*size));
								buffer_top.push_back(Vector2f(i*size, j*size));
							}
						} else if (top_active) {
							top_active = false;
							vertices.push_back(Vector2f(i*size, j*size));
							buffer_top.push_back(Vector2f(i*size, j*size));
							edges.push_back(buffer_top);
							buffer_top.clear();
						}
					} else if (!top_active) {
						top_active = true;
						vertices.push_back(Vector2f(i*size, j*size));
						buffer_top.push_back(Vector2f(i*size, j*size));
					}
					if (i != width-1) {
						if (!map[i+1][j]) {
							if (!bottom_active) {
								bottom_active = true;
								vertices.push_back(Vector2f(i*size+size, j*size));
								buffer_bottom.push_back(Vector2f(i*size+size, j*size));
							}
						} else if (bottom_active) {
							bottom_active = false;
							vertices.push_back(Vector2f(i*size+size, j*size));
							buffer_bottom.push_back(Vector2f(i*size+size, j*size));
							edges.push_back(buffer_bottom);
							buffer_bottom.clear();
						}
					} else if (!bottom_active) {
						bottom_active = true;
						vertices.push_back(Vector2f(i*size+size, j*size));
						buffer_bottom.push_back(Vector2f(i*size+size, j*size));
					}
				} else {
					if (top_active) {
						top_active = false;
						vertices.push_back(Vector2f(i*size, j*size));
						buffer_top.push_back(Vector2f(i*size, j*size));
						edges.push_back(buffer_top);
						buffer_top.clear();
					}
					if (bottom_active) {
						bottom_active = false;
						vertices.push_back(Vector2f(i*size+size, j*size));
						buffer_bottom.push_back(Vector2f(i*size+size, j*size));
						edges.push_back(buffer_bottom);
						buffer_bottom.clear();
					}
				}
			}
			if (top_active) {
				top_active = false;
				vertices.push_back(Vector2f(i*size, height*size));
				buffer_top.push_back(Vector2f(i*size, height*size));
				edges.push_back(buffer_top);
				buffer_top.clear();
			}
			if (bottom_active) {
				bottom_active = false;
				vertices.push_back(Vector2f(i*size+size, height*size));
				buffer_bottom.push_back(Vector2f(i*size+size, height*size));
				edges.push_back(buffer_bottom);
				buffer_bottom.clear();
			}
		}

		top_active = false;
		bottom_active = false;
		buffer_top.clear();
		buffer_bottom.clear();

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (map[j][i]) {
					if (i != 0) {
						if (!map[j][i-1]) {
							if (!top_active) {
								top_active = true;
								buffer_top.push_back(Vector2f(j*size, i*size));
							}
						} else if (top_active) {
							top_active = false;
							buffer_top.push_back(Vector2f(j*size, i*size));
							edges.push_back(buffer_top);
							buffer_top.clear();
						}
					} else if (!top_active) {
						top_active = true;
						buffer_top.push_back(Vector2f(j*size, i*size));
					}
					if (i != height-1) {
						if (!map[j][i+1]) {
							if (!bottom_active) {
								bottom_active = true;
								buffer_bottom.push_back(Vector2f(j*size, i*size+size));
							}
						} else if (bottom_active) {
							bottom_active = false;
							buffer_bottom.push_back(Vector2f(j*size, i*size+size));
							edges.push_back(buffer_bottom);
							buffer_bottom.clear();
						}
					} else if (!bottom_active) {
						bottom_active = true;
						buffer_bottom.push_back(Vector2f(j*size, i*size+size));
					}
				} else {
					if (top_active) {
						top_active = false;
						buffer_top.push_back(Vector2f(j*size, i*size));
						edges.push_back(buffer_top);
						buffer_top.clear();
					}
					if (bottom_active) {
						bottom_active = false;
						buffer_bottom.push_back(Vector2f(j*size, i*size+size));
						edges.push_back(buffer_bottom);
						buffer_bottom.clear();
					}
				}
			}
			if (top_active) {
				top_active = false;
				buffer_top.push_back(Vector2f(width*size, i*size));
				edges.push_back(buffer_top);
				buffer_top.clear();
			}
			if (bottom_active) {
				bottom_active = false;
				buffer_bottom.push_back(Vector2f(width*size, i*size+size));
				edges.push_back(buffer_bottom);
				buffer_bottom.clear();
			}
		}

		for (int i = 0; i < vertices.size(); i++)
			for (int j = 0; j < vertices.size(); j++)
				if (vertices[i] == vertices[j] && i != j)
					vertices.erase(vertices.begin()+j);
	}

public:

	VideoMode getVideoMode () 
	{ return VideoMode(size*width, size*height); }

	void setSize (int setup_size) { setup(setup_size, width, height, color); }
	void setWidth (int setup_width) { setup(size, setup_width, height, color); }
	void setHeight (int setup_height) { setup(size, width, setup_height, color); }
	void setColor (Color setup_color) { color = setup_color; }

	vector<Vector2f>& getVertices () { return vertices; }
	vector<vector<Vector2f>>& getEdges () { return edges; }
	Vector2f getBounds () { return Vector2f(width*size, height*size); }
	int getSize () { return size; }
	int getWidth () { return width; }
	int getHeight () { return height; }
	bool** getMap () { return map; }

	void setTile (Vector2i position) {
		int x = position.x / size;
		int y = position.y / size;
		if (x < 0 || x >= width || y < 0 || y >= height)
			return;
		if (!map[x][y]) {
			map[x][y] = true;
			tiles.push_back(RectangleShape(Vector2f(size, size)));
			tiles.back().setPosition(Vector2f(x*size, y*size));
			tiles.back().setFillColor(color);
			update();
		}
	}

	void cleanTiles () { 
		tiles.clear();
		for (int i = 0; i < width; i++)
			for (int j = 0; j < height; j++)
				map[i][j] = false;
		update();
	}

	void popTile () {
		if (!tiles.empty()) {
			map[int(tiles.back().getPosition().x / size)][int(tiles.back().getPosition().y) / size] = false;
			tiles.pop_back();
		}
		update();
	}

	void draw (RenderWindow* window) {
		for (int i = 0; i < tiles.size(); i++)
			window->draw(tiles[i]);
	}

};


class ShadowMap {
private:

	TileMap* Map;
	struct Vertice {
		Vector2f point;
		float angle;
		float length;
	};
	vector<Vertice> vertices;
	vector<Vertice> single_vertices;
	VertexArray shadow;
	Vector2f MousePosition;
	double t;
	float x1;
	float y1;
	float x2;
	float y2;

	VertexArray rays;
	vector<CircleShape> points;

public:

	ShadowMap (TileMap* setup_Map) {
		Map = setup_Map;
		shadow.setPrimitiveType(TriangleFan);
	}

private:

	float getLength (Vector2f point) 
	{ return sqrt(pow(point.x - MousePosition.x, 2) + pow(point.y - MousePosition.y, 2)); }

	float getAngle (Vector2f point) {
		Vector2f sides  = Vector2f(MousePosition) - Vector2f(point);
		float angle = atan2(sides.y, sides.x) * 180 / PI * -1 + 180;
		return angle;
	}

	bool checkEdge (Vector2f vertex, vector<Vector2f> edge) {
		x1 = edge[0].x;
		y1 = edge[0].y;
		x2 = edge[1].x;
		y2 = edge[1].y;
		float x3 = MousePosition.x;
		float y3 = MousePosition.y;
		float x4 = vertex.x;
		float y4 = vertex.y;
		
		double den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
		if (den == 0)
			return false;
		t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
		double u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den;

		if (t > 0 && t < 1 && u > 0)
			return true;

		return false;
	}

	Vector2f getPoint() {
		Vector2f point;
		point.x = x1 + t * (x2 - x1);
		point.y = y1 + t * (y2 - y1);
		return point;
	}

	bool special_case (Vector2f point) {

		int size = Map->getSize();
		int width = Map->getWidth();
		int height = Map->getHeight();
		bool** map = Map->getMap();

		int x = point.x / size;
		int y = point.y / size;

		cout << x << " <<>> " << y << endl;

		if (x-1 >= 0 && y-1 >= 0 && x <= width-1 && y <= height-1) {
			if (map[x-1][y-1] && map[x][y]) {
				cout << "YEESSSS_1" << endl;
				return true;
			}
		}
		if (x-1 >= 0 && y+1 <= height-1 && x <= width-1 && y <= height-1) {
			if (map[x-1][y] && map[x][y-1]) {
				cout << "YEESSSS_2" << endl;
				return true;
			}
		}

		return false;
	}

	void push_vertex (Vertice buffer, Vertice vertex, bool before) {

		bool special = special_case(vertex.point);

		bool check_here = false;
		if (vertex.point.x / 25 == 1 && vertex.point.y / 25 == 25) {
			cout << vertices.size() << "HEREEE"  << special << endl;
			check_here = true;
		}
		if (check_here)
			cout << "1 -----------" << endl;

		if (vertices.empty()) {
			if (!special) {
				if (before) {
					vertices.push_back(vertex);
					vertices.push_back(buffer);
				} else {
					vertices.push_back(buffer);
					vertices.push_back(vertex);
				}
			} else {
				vertices.push_back(vertex);
				if (check_here)
					cout << "1 -----------" << endl;
			}
		} else {

			for (int i = 0; i < vertices.size(); i++) {
				if (i == vertices.size()-1) {
					if (vertices[i].angle > vertex.angle) {
						if (!special) {
							if (before) {
								vertices.insert(vertices.begin()+i, buffer);
								vertices.insert(vertices.begin()+i, vertex);
								break;
							} else {
								vertices.insert(vertices.begin()+i, vertex);
								vertices.insert(vertices.begin()+i, buffer);
								break;
							}
						} else {
							if (check_here)
								cout << "1 -----------" << endl;
							vertices.insert(vertices.begin()+i, vertex);
							break;
						}
					} else if (vertices[i].angle == vertex.angle) {
						//cout << vertex.angle << " <==== " << endl;
						if (!special) {
							if (vertices[i].length > vertex.length) {
								if (i-1 >= 0) {
									if (vertices[i-1].angle == vertices[i].angle) {
										if (before) {
											vertices[i-1] = vertex;
											vertices[i] = buffer;
											break;
										} else {
											vertices[i-1] = buffer;
											vertices[i] = vertex;
											break;
										}
									} else {
										if (before) {
											vertices[i] = buffer;
											vertices.insert(vertices.begin()+i, vertex);
											break;
										} else {
											vertices[i] = vertex;
											vertices.insert(vertices.begin()+i, buffer);
											break;
										}
									}
								} else {
									if (before) {
										vertices[i] = buffer;
										vertices.insert(vertices.begin()+i, vertex);
										break;
									} else {
										vertices[i] = vertex;
										vertices.insert(vertices.begin()+i, buffer);
										break;
									}
								}
							}
						} else {
							if (check_here)
								cout << "1 -----------" << endl;
							if (vertices[i].length > vertex.length) {
								if (i-1 >= 0) {
									if (vertices[i-1].angle == vertices[i].angle) {
										vertices[i] = vertex;
										vertices.erase(vertices.begin()+i-1);
										break;
									} else {
										vertices[i] = vertex;
										break;
									}
								} else {
									vertices[i] = vertex;
										break;
								}
							}
						}
					} else {
						if (!special) {
							if (before) {
								vertices.push_back(vertex);
								vertices.push_back(buffer);
								break;
							} else {
								vertices.push_back(buffer);
								vertices.push_back(vertex);
								break;
							}
						} else {
							if (check_here)
								cout << "1 -----------" << endl;
							vertices.push_back(vertex);
							break;
						}
					}

				} else if (i == 0) {
					if (check_here)
						cout << "1 -----------" << endl;
					if (vertices[i].angle > vertex.angle) {
						if (!special) {
							if (before) {
								vertices.insert(vertices.begin()+i, buffer);
								vertices.insert(vertices.begin()+i, vertex);
								break;
							} else {
								vertices.insert(vertices.begin()+i, vertex);
								vertices.insert(vertices.begin()+i, buffer);
								break;
							}
						} else {
							if (check_here)
								cout << "1 -----------" << endl;
							vertices.insert(vertices.begin()+i, vertex);
							break;
						}
					} else if (vertices[i].angle == vertex.angle) {
						//cout << vertex.angle << " <==== " << endl;
						if (!special) {
							if (vertices[i].length > vertex.length) {
								if (vertices[i+1].angle == vertices[i].angle) {
									if (before) {
										vertices[i] = vertex;
										vertices[i+1] = buffer;
										break;
									} else {
										vertices[i] = buffer;
										vertices[i+1] = vertex;
										break;
									}
								} else {
									if (before) {
										vertices[i] = buffer;
										vertices.insert(vertices.begin()+i, vertex);
										break;
									} else {
										vertices[i] = vertex;
										vertices.insert(vertices.begin()+i, buffer);
										break;
									}
								}
							}
						} else {
							if (check_here)
								cout << "1 -----------" << endl;
							if (vertices[i].length > vertex.length) {
								if (vertices[i+1].angle == vertices[i].angle) {
									vertices[i] = vertex;
									vertices.erase(vertices.begin()+i+1);
									break;
								} else {
									vertices[i] = vertex;
									break;
								}
							}
						}
					}
				} else {
					if (check_here)
						cout << "1 -----------" << endl;
					if (vertices[i].angle > vertex.angle) {
						if (!special) {
							if (before) {
								vertices.insert(vertices.begin()+i, buffer);
								vertices.insert(vertices.begin()+i, vertex);
								break;
							} else {
								vertices.insert(vertices.begin()+i, vertex);
								vertices.insert(vertices.begin()+i, buffer);
								break;
							}
						} else {
							if (check_here)
								cout << "1 -----------" << endl;
							vertices.insert(vertices.begin()+i, vertex);
							break;
						}
					} else if (vertices[i].angle == vertex.angle) {
						//cout << vertex.angle << " <==== " << endl;
						if (!special) {
							if (vertices[i].length > vertex.length) {
								if (vertices[i+1].angle == vertices[i].angle) {
									if (before) {
										vertices[i] = vertex;
										vertices[i+1] = buffer;
										break;
									} else {
										vertices[i] = buffer;
										vertices[i+1] = vertex;
										break;
									}
								} else if (vertices[i-1].angle == vertices[i].angle) {
									if (before) {
										vertices[i-1] = vertex;
										vertices[i] = buffer;
										break;
									} else {
										vertices[i-1] = buffer;
										vertices[i] = vertex;
										break;
									}
								} else {
									if (before) {
										vertices[i] = buffer;
										vertices.insert(vertices.begin()+i, vertex);
										break;
									} else {
										vertices[i] = vertex;
										vertices.insert(vertices.begin()+i, buffer);
										break;
									}
								}
							}
						} else {
							if (check_here)
								cout << "1 -----------" << endl;
							if (vertices[i].length > vertex.length) {
								if (vertices[i+1].angle == vertices[i].angle) {
									vertices[i] = vertex;
									vertices.erase(vertices.begin()+i+1);
									break;
								} else if (vertices[i-1].angle == vertices[i].angle) {
									vertices[i] = vertex;
									vertices.erase(vertices.begin()+i-1);
									break;
								} else {
									vertices[i] = vertex;
									break;
								}
							}
						}
					}
				}
			}

		}


		//cout << buffer.angle << " " << vertex.angle << endl;



		/*vertices.push_back(buffer);
		vertices.push_back(vertex);*/
		return;
	}

	void push_vertex () {

		/*if (vertices.empty()) {
				vertices.push_back(vertex);
		} else {

			for (int i = 0; i < vertices.size(); i++) {
				if (i == 0) {
					if (vertices[i].angle > vertex.angle) {
						vertices.insert(vertices.begin()+i, vertex);
						break;
					} else if (vertices[i].angle == vertex.angle) {
						if (vertices[i].length > vertex.length){
							vertices[i] = vertex;
							break;
						}
					}
				} else if (i == vertices.size()-1) {
					if (vertices[i].angle > vertex.angle) {
						vertices.insert(vertices.begin()+i, vertex);
						break;
					} else if (vertices[i].angle == vertex.angle) {
						if (vertices[i].length > vertex.length) {
							vertices[i] = vertex;
							break;
						}
					} else {
						vertices.push_back(vertex);
						break;
					}

				} else {
					if (vertices[i].angle > vertex.angle) {
						vertices.insert(vertices.begin()+i, vertex);
						break;
					} else if (vertices[i].angle == vertex.angle) {
						if (vertices[i].length > vertex.length) {
							vertices[i] = vertex;
							break;
						}
					}
				}
			}

		}*/
		bool found;
		for (int i = 0; i < single_vertices.size(); i++) {
			found = false;
			for (int j = 0; j < vertices.size(); j++) {
				if (single_vertices[i].angle == vertices[j].angle) {
					found = true;
					if (single_vertices[i].length < vertices[j].length) {
						vertices[j] = single_vertices[i];
						if (j < vertices.size()-1)
							if (vertices[j+1].angle == single_vertices[i].angle)
								vertices.erase(vertices.begin()+j+1);
						if (j > 0)
							if (vertices[j-1].angle == single_vertices[i].angle)
								vertices.erase(vertices.begin()+j-1);
					}
					break;
				} else if (single_vertices[i].angle < vertices[j].angle) {
					vertices.insert(vertices.begin()+j, single_vertices[i]);
					found = true;
					break;
				}
			}
			if (!found)
				vertices.push_back(single_vertices[i]);
		}

		/*for (int i = 0; i < vertices.size(); i++) {
			if (vertex.angle == vertices[i].angle) {
				if (vertex.length < vertices[i].length) {
					vertices[i] = vertex;
					if (i < vertices.size()-1)
						if (vertices[i+1].angle == vertex.angle)
							vertices.erase(vertices.begin()+i+1);
					if (i > 0)
						if (vertices[i-1].angle == vertex.angle)
							vertices.erase(vertices.begin()+i-1);
					return;
				}
			}
		}*/

		//cout  << vertex.angle << " BOLD ++++ " << endl;

		//vertices.push_back(vertex);

		return;
	}


public:

	void update (RenderWindow* window) {

		vertices.clear();
		single_vertices.clear();
		Vertice buffer;
		float distance;
		float alpha;
		bool buffer_empty;
		MousePosition = Vector2f(Mouse::getPosition(*window));

		bool before = true;
		Vertice order_before;
		Vertice order_after;
		Vertice order_before_buffer;
		Vertice order_after_buffer;
		bool order_before_buffer_empty;
		bool order_after_buffer_empty;

		for (int i = 0; i < Map->getVertices().size(); i++) {
			buffer_empty = true;
			order_before_buffer_empty = true;
			order_after_buffer_empty = true;

			distance = getLength(Map->getVertices()[i]);
			alpha = getAngle(Map->getVertices()[i]);

			order_before.angle = alpha-1;
			order_after.angle = alpha+1;
			order_before.point = Vector2f(MousePosition);
			order_after.point = Vector2f(MousePosition);
			int k;
			order_before.point += Vector2f(1, -tan(order_before.angle / 180 * PI));
			order_after.point += Vector2f(1, -tan(order_after.angle / 180 * PI));


			for (int j = 0; j < Map->getEdges().size(); j++) {
				if (checkEdge(Map->getVertices()[i], Map->getEdges()[j])) {
					Vector2f point = getPoint();
					float length = getLength(point);
					if (buffer_empty) {
						buffer = { point, alpha, length };
						buffer_empty = false;
					} else if (length < buffer.length)
						buffer = { point, alpha, length };
				}
				if (checkEdge(order_before.point, Map->getEdges()[j])) {
					Vector2f point = getPoint();
					float length = getLength(point);
					if (order_before_buffer_empty) {
						order_before_buffer = { point, order_before.angle, length };
						order_before_buffer_empty = false;
					} else if (length < order_before_buffer.length)
						order_before_buffer = { point, order_before.angle, length };
				}
				if (checkEdge(order_after.point, Map->getEdges()[j])) {
					Vector2f point = getPoint();
					float length = getLength(point);
					if (order_after_buffer_empty) {
						order_after_buffer = { point, order_after.angle, length };
						order_after_buffer_empty = false;
					} else if (length < order_after_buffer.length)
						order_after_buffer = { point, order_after.angle, length };
				}
			}
			if (!buffer_empty) {
				if(buffer.length > distance) {
					if (!order_before_buffer_empty && !order_after_buffer_empty)
						if (order_before_buffer.length > order_after_buffer.length) {
							cout << order_before_buffer.length << "||||" << order_after_buffer.length << endl;
							before = true;
						}
					push_vertex(buffer, { Map->getVertices()[i], alpha, distance }, before);
				}
			} else {
				single_vertices.push_back({ Map->getVertices()[i], alpha, distance });
			}
		}
		push_vertex();
	}

	void draw (RenderWindow* window) {
		cout << "=================" << endl;
		points.clear();
		rays.clear();
		rays.setPrimitiveType(Lines);
		shadow.clear();

		shadow.append(Vertex(Vector2f(MousePosition), Color(255, 255, 255, 50)));
		for (int i = 0; i < vertices.size(); i++) {
			rays.append(Vertex(Vector2f(MousePosition), Color::White));
			rays.append(Vertex(Vector2f(vertices[i].point), Color::White));
			points.push_back(CircleShape(3.f));
			points.back().setOrigin(Vector2f(3.f, 3.f));
			points.back().setPosition(Vector2f(vertices[i].point));
			points.back().setFillColor(Color::Red);
			cout << vertices[i].angle << " " << vertices[i].length << endl;
			shadow.append(Vertex(Vector2f(vertices[i].point), Color(255, 255, 255, 50)));
		}
		if (!vertices.empty())
			shadow.append(Vertex(Vector2f(vertices[0].point), Color(255, 255, 255, 50)));
		window->draw(rays);
		window->draw(shadow);
		for (int i = 0; i < points.size(); i++) {
			window->draw(points[i]);
		}
		return;
	}

};


int main () {

	TileMap Map;
	Map.setColor(Color(31, 58, 147, 255));
	Map.setWidth(36);
	Map.setHeight(26);

	ShadowMap Shadow(&Map);

	RenderWindow window(Map.getVideoMode(), "Shadow 2.0");
	window.setFramerateLimit(60);

	cout << window.getSize().x << " " << window.getSize().y << endl;

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Escape)
					window.close();
				if (event.key.code == Keyboard::Z)
					Map.popTile();
				if (event.key.code == Keyboard::X)
					Map.cleanTiles();
			}
		}

		if (Mouse::isButtonPressed(Mouse::Left))
			Map.setTile(Mouse::getPosition(window));

		Shadow.update(&window);

		window.clear();
		Map.draw(&window);
		Shadow.draw(&window);
		window.display();

	}

	return 0;
}
