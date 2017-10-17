CC = gcc
CFLAGS = -g -O0 $(shell pkg-config --cflags ImageMagick)

UNITS = rgb vertex normal surface
TESTS = $(addprefix test_,$(UNITS))
OBJECTS = $(addsuffix .o,$(UNITS) $(TESTS))

all: fsim tetraeder mini test-fsim

check: test-fsim
	./test-fsim

fsim: fsim.o CuTest.o
	$(CC) -o $@ fsim.o CuTest.o -lglut -lGLEW -lGLU -lGL $(shell pkg-config --libs ImageMagick) -lgc -lm

tetraeder: tetraeder.o
	$(CC) -o $@ tetraeder.o -lglut -lGLEW -lGLU -lGL -lm

mini: mini.o CuTest.o
	$(CC) -o $@ mini.o CuTest.o -lglut -lGLEW -lGLU -lGL -lm

test-fsim: test_fsim.o $(OBJECTS) munit.o
	$(CC) -o $@ test_fsim.o $(OBJECTS) munit.o -lgomp -lgc

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f fsim tetraeder mini test-fsim *.o *.ppm
