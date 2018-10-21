CC=gcc
CFLAGS=-std=c99 -Wall -Wextra

CPP=g++
CPPFLAGS=

SDLDEPS=-lm -lSDL -lSDLmain -lSDL_image

LDFLAGS=
EXEC=sdl_ocr

all: $(EXEC)

sdl_ocr: pixel.o process.o output.o main.o
	$(CC) -o sdl_ocr pixel.o process.o output.o main.o $(LDFLAGS) $(SDLDEPS)

pixel.o: pixel.c pixel.h
	$(CC) -o pixel.o -c pixel.c $(CFLAGS)

process.o: process.c process.h
	$(CC) -o process.o -c process.c $(CFLAGS)

output.o: output.c output.h
	$(CC) -o output.o -c output.c $(CFLAGS)

main.o: main.c
	$(CC) -o main.o -c main.c $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
