#CC = gcc # Flag for implicit rules
#CFLAGS = -g # Flag for implicit rules. Turn on debug info

opengl.out: main.c
	gcc -o opengl.out -Wall main.c -lglut -lGL

all: opengl.out

clean:
	rm -f *.out
