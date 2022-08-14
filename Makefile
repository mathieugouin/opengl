#CC = gcc # Flag for implicit rules
#CFLAGS = -g # Flag for implicit rules. Turn on debug info

EXE = opengl.out

opengl.out: main.c
	gcc -o $(EXE) -Wall main.c -lglut -lGL

all: $(EXE)

check:
	ls -l $(EXE)

clean:
	rm -f *.out
