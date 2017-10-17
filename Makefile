CC = gcc
CFLAGS = -g -O0 $(shell pkg-config --cflags ImageMagick)

all: fsim tetraeder mini

check: fsim
	./fsim

fsim: fsim.o CuTest.o
	$(CC) -o $@ fsim.o CuTest.o -lglut -lGLEW -lGLU -lGL $(shell pkg-config --libs ImageMagick) -lgc -lm

tetraeder: tetraeder.o
	$(CC) -o $@ tetraeder.o -lglut -lGLEW -lGLU -lGL -lm

mini: mini.o CuTest.o
	$(CC) -o $@ mini.o CuTest.o -lglut -lGLEW -lGLU -lGL -lm

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f fsim tetraeder mini *.o *.ppm
