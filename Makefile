#CC = gcc # Flag for implicit rules
#CFLAGS = -g # Flag for implicit rules. Turn on debug info

opengl: main.c
	gcc -o opengl -Wall main.c -lglut -lGL

all: opengl

clean:
	rm -f opengl
