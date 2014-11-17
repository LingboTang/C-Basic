mention: mention.o
	gcc -Wall -std=c99 -o mention mention.o -lm

mention.o: mention.c 
	gcc -Wall -std=c99 -c mention.c

clean:
	-rm -f *.o mention core
tar:
	tar cvf submit.tar mention.c Makefile README testcases.txt
