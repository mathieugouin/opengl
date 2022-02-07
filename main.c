#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>

//Compile & run with:
//  gcc main.c -lglut -lGL && ./a.out

#define WINDOW_WIDTH 300
#define WINDOW_HEIGHT 300

void displayMe(void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glClear (GL_COLOR_BUFFER_BIT);
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
    //glOrtho(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT, -1.0, 1.0);

    glColor3f (0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
        glVertex3f (0.25, 0.25, 0.0);
        glVertex3f (0.75, 0.25, 0.0);
        glVertex3f (0.75, 0.75, 0.0);
        glVertex3f (0.25, 0.75, 0.0);
    glEnd();

    glFlush();
}

int main(int argc, char** argv)
{
    printf("Open GL Test\n");

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);

    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL");
    glutDisplayFunc(displayMe);
    glutMainLoop();

    return EXIT_SUCCESS;
}
