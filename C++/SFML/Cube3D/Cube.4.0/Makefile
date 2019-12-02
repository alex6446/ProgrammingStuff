output: main.o Scene.o Camera.o Object3D.o Cube3D.o
	g++ main.o Scene.o Camera.o Object3D.o Cube3D.o -o output -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp
	g++ -c main.cpp

Scene.o: Scene.cpp
	g++ -c Scene.cpp

Camera.o: Camera.cpp
	g++ -c Camera.cpp

Object3D.o: Object3D.cpp
	g++ -c Object3D.cpp

Cube3D.o: Cube3D.cpp
	g++ -c Cube3D.cpp

clean:
	rm *.o output