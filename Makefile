main.exe: main.o 
	g++ -g -Werror -Wall main.o -o main.out

# Per il codice templato e' importante mettere i file .h
# tra le dipendenze per far rilevare a make le modifiche
# al codice della classe
main.o: main.cpp sparsematrix.hpp
	g++ -c -Werror -Wall main.cpp -o main.o

.PHONY: clean

clean:
	rm *.out *.o
