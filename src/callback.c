#include <math.h>
#include <GL/glut.h>
#include "display.h"
#include "perspective.h"
#include "shader.h"
#include "callback.h"

static void callback_display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    display_draw();
    glutSwapBuffers(); 
}

static void callback_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    /* WASD-style controls */
    case 'W':
    case 'w':
        /* forward */
        perspective_move(1);
        break;
    case 'A':
    case 'a':
        /* left */
        perspective_strafe(-1);
        break;
    case 'S':
    case 's':
        /* backward */
        perspective_move(-1);
        break;
    case 'D':
    case 'd':
        /* right */
        perspective_strafe(1);
        break;
    /* miscellaneous controls */
    case 'P':
    case 'p':
        perspective_print();
        break;
#if 0
    case ' ':
        shader_select();
        break;
#endif
    }

    glutPostRedisplay();
}

static void callback_special(int key, int x, int y)
{
	switch (key) {
    case GLUT_KEY_LEFT:
        /* turn left */
        theta -= 0.01;
        break;
    case GLUT_KEY_RIGHT:
        /* turn right */
        theta += 0.01;
        break;
    case GLUT_KEY_UP:
        /* look up */
        phi -= 0.01;
        break;
    case GLUT_KEY_DOWN:
        /* look down */
        phi += 0.01;
        break;
	}

    perspective_turn(phi, theta);
    glutPostRedisplay();
}

void callback_init()
{
    glutDisplayFunc(callback_display);
    glutKeyboardFunc(callback_keyboard);
    glutSpecialFunc(callback_special);
}

