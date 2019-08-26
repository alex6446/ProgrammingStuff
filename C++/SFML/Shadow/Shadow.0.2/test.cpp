#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <SFML/Graphics.hpp>

#define PI 3.14159265

using namespace sf;
using namespace std;

int main()
{
    RenderWindow window(VideoMode(680, 450), "Test Vertex Array");
    window.setFramerateLimit(60);
    
    srand(time(NULL));

    VertexArray vertices(TriangleFan);
    vector<CircleShape> circles;

    /*for (int i = 0; i < 7; i++)
    	vertices.append(Vertex(Vector2f(rand()%window.getSize().x, rand()%window.getSize().y)));*/
    
    for (int i = 0; i < vertices.getVertexCount(); i++) {
    	circles.push_back(CircleShape(3.f));
    	circles.back().setOrigin(Vector2f(3.f, 3.f));
    	circles.back().setPosition(vertices[i].position);
    	circles.back().setFillColor(Color::Red);
    }
    circles[0].setFillColor(Color::Magenta);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(vertices);
        for (int i = 0; i < circles.size(); i++)
        	window.draw(circles[i]);
        window.display();
    }

    return 0;
}