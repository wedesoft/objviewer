all: fsim tetraeder

check: fsim
	./fsim

fsim: fsim.o CuTest.o
	gcc -o $@ fsim.o CuTest.o -lglut -lGLU -lGL -lgc -lm

tetraeder: tetraeder.o
	gcc -o $@ tetraeder.o -lglut -lGLEW -lGLU -lGL -lm

.c.o:
	gcc -c $< -o $@

clean:
	rm -f fsim tetraeder *.o
