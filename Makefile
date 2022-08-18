INCLUDES=-I ./include
CFLAGS=-Wall -ggdb -std=c11 -pedantic -lm

all: schleptron

schleptron: main.c $(OBJECTS)
	$(CC) $(INCLUDES) $(CFLAGS) main.c -o schleptron

clean:
	rm -rf ./schleptron ./build/* ./*.ppm
