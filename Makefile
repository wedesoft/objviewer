CC = gcc
CFLAGS = -g -O0 $(shell pkg-config --cflags ImageMagick) -DGLEW_STATIC
LIBS = -lGLEW -lglut -lGLU -lGL $(shell pkg-config --libs ImageMagick) -lgc -lgomp -lm

UNITS = rgb vertex normal surface object program shader vertex_array_object image texture texture_coordinate
TESTS = $(addprefix test_,$(UNITS))
OBJECTS = $(addsuffix .o,$(UNITS) $(TESTS))

all: tetraeder tetraeder2 mini testsuite

check: testsuite
	./testsuite

tetraeder: tetraeder.o
	$(CC) -o $@ tetraeder.o $(LIBS)

tetraeder2: tetraeder2.o $(addsuffix .o,$(UNITS)) report_status.o
	$(CC) -o $@ tetraeder2.o $(addsuffix .o,$(UNITS)) report_status.o $(LIBS)

mini: mini.o
	$(CC) -o $@ mini.o $(LIBS)

testsuite: testsuite.o $(OBJECTS) report_status.o test_helper.o munit.o
	$(CC) -o $@ testsuite.o $(OBJECTS) report_status.o test_helper.o munit.o $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f tetraeder tetraeder2 mini testsuite *.o *.ppm
