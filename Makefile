main.exe: main.o 
	g++ -g main.o -o main.out

# Per il codice templato e' importante mettere i file .h
# tra le dipendenze per far rilevare a make le modifiche
# al codice della classe
main.o: main.cpp sparsematrix.hpp
	g++ -c main.cpp -o main.o

.PHONY: clean

clean:
	rm *.out *.o
