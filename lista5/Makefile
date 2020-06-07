# Makefile

all: zad1 zad2 zad3 zad4 clean

zad1: zad1.o PriorityQueue.o 
	g++ -o zad1 zad1.o PriorityQueue.o

zad2: zad2.o GraphDijkstra.o PriorityQueue.o
	g++ -o zad2 zad2.o GraphDijkstra.o PriorityQueue.o

zad3: zad3.o GraphMST.o PriorityQueue.o
	g++ -o zad3 zad3.o GraphMST.o PriorityQueue.o

zad4: zad4.o GraphTravel.o GraphMST.o PriorityQueue.o
	g++ -o zad4 zad4.o GraphTravel.o GraphMST.o PriorityQueue.o

zad1.o: zad1.cpp
	g++ -c zad1.cpp

PriorityQueue.o: src/PriorityQueue.cpp src/PriorityQueue.h
	g++ -c src/PriorityQueue.cpp -o PriorityQueue.o

zad2.o: zad2.cpp
	g++ -c zad2.cpp

GraphDijkstra.o: src/GraphDijkstra.cpp src/GraphDijkstra.h
	g++ -c src/GraphDijkstra.cpp -o GraphDijkstra.o

zad3.o: zad3.cpp
	g++ -c zad3.cpp

GraphMST.o: src/GraphMST.cpp src/GraphMST.h
	g++ -c src/GraphMST.cpp -o GraphMST.o

zad4.o: zad4.cpp
	g++ -c zad4.cpp

GraphTravel.o: src/GraphTravel.cpp src/GraphTravel.h
	g++ -c src/GraphTravel.cpp -o GraphTravel.o

clean:
	rm -f *.o
