output: main.o book.o
	g++ main.o book.o -o output

main.o: main.cpp
	g++ -c main.cpp

book.o: book.cpp book.h
	g++ -c book.cpp

clean:
	rm *.o output