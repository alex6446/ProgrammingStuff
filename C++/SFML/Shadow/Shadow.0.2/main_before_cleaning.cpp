#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>

#define PI 3.14159265

using namespace sf;
using namespace std;

/*struct EdgesDraw {
	Vertex cords[2];
};*/

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

	/*vector<EdgesDraw> edges_draw;
	vector<CircleShape> vertices_draw;*/

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

		/*for (int i = 0; i < vertices.size(); i++)
			cout << vertices[i].x << " " << vertices[i].y << endl;
		cout << "=========================" << endl;*/
		
		/*for (int i = 0; i < edges.size(); i++) {
			cout << edges[i][0].x << " " << edges[i][0].y << " -------- ";
			cout << edges[i][1].x << " " << edges[i][1].y << endl;
		}
		cout << "=========================" << endl;*/


		/*edges_draw.clear();
		EdgesDraw temp;
		for (int i = 0; i < edges.size(); i++) {
			temp.cords[0] = Vertex(edges[i][0], Color::Red);
			temp.cords[1] = Vertex(edges[i][1], Color::Red);
			edges_draw.push_back(temp);
		}

		vertices_draw.clear();
		for (int i = 0; i < vertices.size(); i++) {
			vertices_draw.push_back(CircleShape(3.f));
			vertices_draw.back().setPosition(Vector2f(vertices[i]));
			vertices_draw.back().setOrigin(Vector2f(3.f, 3.f));
		}*/
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
		/*for (int i = 0; i < edges_draw.size(); i++)
			window->draw(edges_draw[i].cords, 2, Lines);
		for (int i = 0; i < vertices_draw.size(); i++)
			window->draw(vertices_draw[i]);*/
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
	VertexArray shadow;
	Vector2f MousePosition;
	double t;
	float x1;
	float y1;
	float x2;
	float y2;

	VertexArray rays;

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

	/*bool checkEdge (Vector2f vertex, vector<Vector2f> edge) {

		Vector2f sides  = Vector2f(MousePosition) - Vector2f(vertex);
		Vector2f sides1 = Vector2f(MousePosition) - Vector2f(edge[0]);
		Vector2f sides2 = Vector2f(MousePosition) - Vector2f(edge[1]);
		float vertex_angle = atan2(sides.y, sides.x) * 180 / PI * -1 + 180;
		float angle1 = atan2(sides1.y, sides1.x) * 180 / PI * -1 + 180;
		float angle2 = atan2(sides2.y, sides2.x) * 180 / PI * -1 + 180;

		if (abs(angle1 - angle2) > 180) {
			if (vertex_angle < min(angle1, angle2) || vertex_angle > max(angle1, angle2)) {
				return true;
			}
		} else {
			if (vertex_angle < max(angle1, angle2) && vertex_angle > min(angle1, angle2)) {
				return true;
			}
		}

		return false;
	}*/

	/*Vector2f getPoint(Vector2f vertex, vector<Vector2f> edge) {

		float edgeBaseX = edge[0].x;
		float edgeBaseY = Map->getBounds().y - edge[0].y;
		if (edge[0].y < edge[1].y) {
			edgeBaseX = edge[1].x;
			edgeBaseY = Map->getBounds().y - edge[1].y;
		}
		float lightBaseX = Mouse::getPosition().x;
		float lightBaseY = Map->getBounds().y - Mouse::getPosition().y;
		Vector2f point;

		Vector2f sides  = Vector2f(Mouse::getPosition()) - Vector2f(vertex);
		float alpha = atan2(sides.y, sides.x) * 180 / PI * -1 + 180;

		float beta = 90;
		if (edge[0].y == edge[1].y)
			beta == 0;

		if (alpha > 180)
			alpha -= 180;

		float edgeK = tan(beta / 180 * PI);
		float edgeB = edgeBaseY - edgeBaseX * edgeK;

		if (alpha == 90.f) {
			point.x = lightBaseX;
			point.y = edgeK * point.x + edgeB;
		} else {
			float lightK = tan(alpha / 180 * PI);
			float lightB = lightBaseY - lightBaseX * lightK;
			point.x = (edgeB - lightB) / (lightK - edgeK);
			point.y = lightK * point.x + lightB;
		}

		point.y = Map->getBounds().y - point.y;

		return point;
	}*/

	/*Vector2f getPoint(Vector2f vertex, vector<Vector2f> edge) {

		Vector2f point;
		float alpha = 90.f;
		if (edge[0].y == edge[1].y)
			apha = 0.f;



	}*/

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

	void push_vertex () {
		return;
	}


public:

	void update (RenderWindow* window) {

		vertices.clear();
		Vertice buffer;
		float distance;
		float alpha;
		bool buffer_empty;
		MousePosition = Vector2f(Mouse::getPosition(*window));

		for (int i = 0; i < Map->getVertices().size(); i++) {
			buffer_empty = true;
			distance = getLength(Map->getVertices()[i]);
			alpha = getAngle(Map->getVertices()[i]);
			for (int j = 0; j < Map->getEdges().size(); j++) {
				if (checkEdge(Map->getVertices()[i], Map->getEdges()[j])) {
					Vector2f point = getPoint();
					float angle = getAngle(point);
					float length = getLength(point);
					if (buffer_empty) {
						buffer = { point, angle, length };
						buffer_empty = false;
					} else if (length < buffer.length)
						buffer = { point, angle, length };
				}
			}
			if (!buffer_empty) {
				if(buffer.length > distance) {
					vertices.push_back(buffer);
					vertices.push_back({ Map->getVertices()[i], alpha, distance });
				}
			} else {
				vertices.push_back({ Map->getVertices()[i], alpha, distance });
			}
		}
		
	}

	void draw (RenderWindow* window) {

		rays.clear();
		rays.setPrimitiveType(Lines);
		for (int i = 0; i < vertices.size(); i++) {
			rays.append(Vertex(Vector2f(MousePosition), Color::White));
			rays.append(Vertex(Vector2f(vertices[i].point), Color::White));
		}
		window->draw(rays);
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
