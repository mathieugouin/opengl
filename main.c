#include <stdio.h>
#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glut.h>

//Compile & run with:
//  gcc main.c -lglut -lGL && ./a.out

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 800

void keyboard(unsigned char key, int x, int y)
{
  switch (key)
  {
    /* Exit on escape key press */
    case '\x1B':
    {
      exit(EXIT_SUCCESS);
      break;
    }
  }
}

void displayMe(void)
{
    printf("displayMe\n");
    glClearColor (0.0, 0.0, 0.0, 1.0);
    glClear (GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT, -1.0, 1.0);
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f (0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
        glVertex3f (10.0, 10.0, 0.0);
        glVertex3f (10.0, WINDOW_HEIGHT - 10, 0.0);
        glVertex3f (WINDOW_WIDTH - 10, WINDOW_HEIGHT - 10, 0.0);
        glVertex3f (WINDOW_WIDTH - 10, 10.0, 0.0);
    glEnd();

    glFlush();
}

int main(int argc, char** argv)
{
    printf("Open GL Test\n");

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);

    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("OpenGL");

    glutDisplayFunc(displayMe);
    glutKeyboardFunc(&keyboard);

    glutMainLoop();

    return EXIT_SUCCESS;
}

