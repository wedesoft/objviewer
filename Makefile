all: test fsim

test: test.o
	gcc -o $@ $< -lglut -lGLU -lGL -lm

fsim: fsim.o
	gcc -o $@ $< -lglut -lGLEW -lGLU -lGL -lm

.c.o:
	gcc -c $< -o $@

clean:
	rm -f test fsim *.o
