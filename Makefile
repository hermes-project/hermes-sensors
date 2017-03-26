main: main.o Srf02.o
	g++ -o main main.o Srf02.o

main.o: main.cpp
	g++ -Wall -c main.cpp

Srf02.o: Srf02.cpp Srf02.hpp
	g++ -Wall -c Srf02.cpp

clean:
	rm *.o
