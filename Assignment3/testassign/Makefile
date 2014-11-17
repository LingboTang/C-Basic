lander: lander.o
	gcc -Wall -std=c99 -o lander lander.o -lm -l curses

lander.o: lander.c 
	gcc -Wall -std=c99 -c lander.c -l curses

clean:
	-rm -f *.o lander core
