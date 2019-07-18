output: main.o figure.o
	g++ main.o figure.o -o output

main.o: main.cpp
	g++ -c main.cpp

figure.o: figure.cpp geometry.h
	g++ -c figure.cpp

circle.o: circle.cpp geometry.h
	g++ -c circle.cpp

clean:
	rm *.o output