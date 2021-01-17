CC = gcc
FLAGS = -Wall 

all: frequency 

frequency: frequency.c
	$(CC) $(FLAGS)  -o frequency frequency.c 

.PHONY: clean

clean:
	rm -rf *.o *.a *.gch *.so 
