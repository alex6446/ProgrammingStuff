output: mainSFML.o
	g++ mainSFML.o -o output -lsfml-graphics -lsfml-window -lsfml-system

main.o: mainSFML.cpp
	g++ -c mainSFML.cpp

clean:
	rm *.o output