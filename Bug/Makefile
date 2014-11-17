# This Makefile does not have great style.
# Type make to create bug.
# debug option (gcc's -g flag) is already enabled

DEBUG=-g
CC=gcc
CFLAGS=-std=c99 -Wall $(DEBUG)
EXEC=bug

$(EXEC): $(EXEC).c

clean:
	-rm -f core $(EXEC)
