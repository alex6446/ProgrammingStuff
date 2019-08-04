output: main.o
	g++ main.o -o output -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp SFMLConsole.hpp
	g++ -c main.cpp

clean:
	rm *.o output