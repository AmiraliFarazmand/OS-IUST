CC = gcc
CFLAGS =  -Wall -Wextra -O3 -g -lpthread -lrt -lm

OBJECTS = main.o

default: $(OBJECTS)

%.o: %.c
	$(CC) -o$@ $< $(CFLAGS)

clean:
	rm *.o
