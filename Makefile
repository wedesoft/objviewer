CC = gcc
CFLAGS = -Werror -ansi

all: fsim tetraeder

check: fsim
	./fsim

fsim: fsim.o CuTest.o
	$(CC) -o $@ fsim.o CuTest.o -lglut -lGLU -lGL -lgc -lm

tetraeder: tetraeder.o
	$(CC) -o $@ tetraeder.o -lglut -lGLEW -lGLU -lGL -lm

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f fsim tetraeder *.o
