fsim: fsim.o
	gcc -o $@ $< -lglut -lGLEW -lGLU -lGL -lm

.c.o:
	gcc -c $< -o $@

clean:
	rm -f fsim *.o
