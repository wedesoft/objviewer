CC = gcc
CFLAGS = -g -O0 $(shell pkg-config --cflags ImageMagick) -DGLEW_STATIC
LIBS = -lGLEW -lglut -lGLU -lGL $(shell pkg-config --libs ImageMagick) -lgc -lgomp -lm

UNITS = rgb vertex normal surface object program shader vertex_array_object image texture texture_coordinate
TESTS = $(addprefix test_,$(UNITS))
OBJECTS = $(addsuffix .o,$(UNITS) $(TESTS))

all: tetraeder mini test-fsim

check: test-fsim
	./test-fsim

tetraeder: tetraeder.o
	$(CC) -o $@ tetraeder.o $(LIBS)

mini: mini.o
	$(CC) -o $@ mini.o $(LIBS)

test-fsim: test_fsim.o $(OBJECTS) report_status.o test_helper.o munit.o
	$(CC) -o $@ test_fsim.o $(OBJECTS) report_status.o test_helper.o munit.o $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f tetraeder mini test-fsim *.o *.ppm
