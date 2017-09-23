fsim: fsim.o
	gcc -o $@ $< -lGL -lglut

.c.o:
	gcc -c $< -o $@
