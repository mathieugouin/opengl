#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include <GL/gl.h>
#include <GL/glut.h>

//Compile & run with:
//  gcc -Wall main.c -lglut -lGL && ./a.out

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 800

/*  Create checkerboard texture  */
#define checkImageWidth     300
#define checkImageHeight    400
static GLubyte checkImage[checkImageHeight][checkImageWidth][4];
static GLuint texName;

#define NB_BAND 4

void makeCheckImage(void)
{
    int i, j, c;

    for (i = 0; i < checkImageHeight; i++)
    {
        for (j = 0; j < checkImageWidth; j++)
        {
            c = NB_BAND * i;
            c /= checkImageHeight;  // 0 - 3
            c *= (255 / (NB_BAND - 1));

            checkImage[i][j][0] = c; // RED
            checkImage[i][j][1] = 0; // GREEN

            c = NB_BAND * j;
            c /= checkImageWidth;  // 0 - 3
            c *= (255 / (NB_BAND - 1));

            checkImage[i][j][2] = c; // BLUE
            checkImage[i][j][3] = 255; // ALPHA
        }
    }
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);

    makeCheckImage();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glGenTextures(1, &texName);
    glBindTexture(GL_TEXTURE_2D, texName);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  // linear filter for magnification
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  // linear filter for minifying

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth,
                 checkImageHeight,
                 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 checkImage);

    glShadeModel(GL_SMOOTH);
}

void keyboard(unsigned char key, int x, int y)
{
    printf("keyboard, key=0x%02d\n", (int)key);

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

float rand_range(float min, float max)
{
    int r;
    float x;
    r = rand();      // Returns a pseudo-random integer between 0 and RAND_MAX.
    x = (float)r / RAND_MAX;
    x *= (max - min);
    x += min;
    return x;
}

void draw_square(void)
{
    // Green square
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_QUADS);
    glVertex3f(10.0, 10.0, 0.0);
    glVertex3f(10.0, WINDOW_HEIGHT - 10, 0.0);
    glVertex3f(WINDOW_WIDTH - 10, WINDOW_HEIGHT - 10, 0.0);
    glVertex3f(WINDOW_WIDTH - 10, 10.0, 0.0);
    glEnd();
}

void draw_points(void)
{
    int i;

    glBegin(GL_POINTS);

    for (i = 0; i < 1000000; i++)
    {
        glColor3f(
                rand_range(0, 1),
                rand_range(0, 1),
                rand_range(0, 1)
                );
        glVertex3f(rand_range(0, WINDOW_WIDTH), rand_range(0, WINDOW_HEIGHT), 0.0);
    }

    glEnd();
}

void draw_texture(void)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texName);

    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); // use color from texture

    glColor3f(0.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(10.0, WINDOW_HEIGHT - 10, 0.0); // top left
    glTexCoord2f(1.0, 0.0);
    glVertex3f(WINDOW_WIDTH - 10, WINDOW_HEIGHT - 10, 0.0); // top right
    glTexCoord2f(1.0, 1.0);
    glVertex3f(WINDOW_WIDTH - 10, 10.0, 0.0);  // bottom right
    glTexCoord2f(0.0, 1.0);
    glVertex3f(10.0, 10.0, 0.0); // bottom left
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void display(void)
{
    static int d = 0;
    printf("display %d\n", d++);

    glClearColor(0.0, 0.0, 0.0, 1.0); // black
    glClear(GL_COLOR_BUFFER_BIT);

    //draw_square();
    draw_points();
    //draw_texture();

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    static int r = 0;
    printf("reshape %d\n", r++);

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void idle_callback(void)
{
    static int i = 0;
    printf("idle_callback %d\n", i++);
}

void timer_callback(int value)
{
    static int c = 0;
    glutTimerFunc(1000, timer_callback, 99);
    printf("timer_callback value=%d, count=%d\n", value, c++);
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    printf("Open GL Test: %s\n", argv[0]);

    srand(time(NULL));   // Initialization, should only be called once.

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("OpenGL");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    //glutIdleFunc(idle_callback);
    glutTimerFunc(1000, timer_callback, 99);

    glutMainLoop();

    return EXIT_SUCCESS;
}
