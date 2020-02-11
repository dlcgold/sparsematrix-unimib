main.out: main.o 
	g++ -g -std=c++0x main.o -o main.out

main.o: main.cpp sparsematrix.h
	g++ -c -std=c++0x main.cpp -o main.o

.PHONY: clean

clean:
	rm *.out *.o
