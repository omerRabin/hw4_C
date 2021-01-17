CC = gcc
FLAGS = -Wall 

all: frequency 

frequency: frequency.c
	$(CC) $(FLAGS) frequency.c -o frequency

.PHONY: clean

clean:
	rm -rf *.o *.a *.gch *.so 
