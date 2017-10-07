all: test fsim

test: test.o CuTest.o
	gcc -o $@ test.o CuTest.o -lglut -lGLU -lGL -lm

fsim: fsim.o
	gcc -o $@ fsim.o -lglut -lGLEW -lGLU -lGL -lm

.c.o:
	gcc -c $< -o $@

clean:
	rm -f test fsim *.o
