fsim: fsim.o
	gcc -o $@ $< -lglut -lGLEW -lGL

.c.o:
	gcc -c $< -o $@

clean:
	rm -f fsim *.o
