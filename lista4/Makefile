# Makefile

all: main clean

main: main.o DataStructure.o BinarySearchTree.o RedBlackTree.o HashMap.o Statistics.o LinkedList.o Bloom.o
	g++ -o main main.o DataStructure.o BinarySearchTree.o RedBlackTree.o HashMap.o Statistics.o LinkedList.o Bloom.o

main.o: main.cpp
	g++ -c main.cpp

DataStructure.o: src/DataStructure.cpp src/DataStructure.h
	g++ -c src/DataStructure.cpp -o DataStructure.o

BinarySearchTree.o: src/BinarySearchTree.cpp src/BinarySearchTree.h
	g++ -c src/BinarySearchTree.cpp -o BinarySearchTree.o

RedBlackTree.o: src/RedBlackTree.cpp src/RedBlackTree.h
	g++ -c src/RedBlackTree.cpp -o RedBlackTree.o

HashMap.o: src/HashMap.cpp src/HashMap.h
	g++ -c src/HashMap.cpp -o HashMap.o

Statistics.o: src/Statistics.cpp src/Statistics.h
	g++ -c src/Statistics.cpp -o Statistics.o

LinkedList.o: src/LinkedList.cpp src/LinkedList.h
	g++ -c src/LinkedList.cpp -o LinkedList.o

Bloom.o: src/Bloom.cpp src/Bloom.h
	g++ -c src/Bloom.cpp -o Bloom.o

clean:
	rm -f *.o
