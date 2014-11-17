filter: filter.o
	gcc -Wall -std=c99 -o filter filter.o -lm

filter.o:filter.c
	gcc -Wall -std=c99 -c filter.c

clean:
	-rm -f *.o filter core
