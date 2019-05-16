output:	main.o scanner.o parser.o testTree.o
	g++ -std=c++0x -Wall main.o scanner.o parser.o testTree.o -o frontEnd

main.o: main.cpp
	g++ -c main.cpp

scanner.o: scanner.cpp  scanner.h
	g++ -c scanner.cpp
parser.o: parser.cpp parser.h
	g++ -c parser.cpp 
testTree.o: testTree.cpp testTree.h 
	g++ -c testTree.cpp

clean:
	rm *.o frontEnd
