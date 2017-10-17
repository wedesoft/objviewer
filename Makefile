CC = gcc
CFLAGS = -g -O0 $(shell pkg-config --cflags ImageMagick)

all: fsim tetraeder mini test-fsim

check: test-fsim
	./test-fsim

fsim: fsim.o CuTest.o
	$(CC) -o $@ fsim.o CuTest.o -lglut -lGLEW -lGLU -lGL $(shell pkg-config --libs ImageMagick) -lgc -lm

tetraeder: tetraeder.o
	$(CC) -o $@ tetraeder.o -lglut -lGLEW -lGLU -lGL -lm

mini: mini.o CuTest.o
	$(CC) -o $@ mini.o CuTest.o -lglut -lGLEW -lGLU -lGL -lm

test-fsim: test_fsim.o test_rgb.o rgb.o test_vertex.o vertex.o test_normal.o normal.o munit.o
	$(CC) -o $@ test_fsim.o test_rgb.o rgb.o test_vertex.o vertex.o test_normal.o normal.o munit.o -lgomp

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f fsim tetraeder mini *.o *.ppm
