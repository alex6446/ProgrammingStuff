output: main.o
	g++ main.o -o output -lglfw -lGLEW -lGLU -lGL -lsoil2

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm *.o output
