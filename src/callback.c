#include <math.h>
#include <stdbool.h>
#include "glut.h"
#include "display.h"
#include "perspective.h"
#include "texture.h"
#include "callback.h"

static void callback_display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    display_draw();
    glutSwapBuffers(); 
}

#include <stdio.h>
static void callback_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    /* WASD-style controls except A and D are not configured */
    case 'W':
    case 'w':
        /* forward */
        perspective_move(1);
        break;
    case 'S':
    case 's':
        /* backward */
        perspective_move(-1);
        break;
    /* miscellaneous controls */
    case 'N':
    case 'n':
        texture_select();
        break;
    case 'R':
    case 'r':
        display_rotate_reset();
        break;
    case ' ':
        shader_select();
        break;
    }

    glutPostRedisplay();
}

static void callback_special(int key, int x, int y)
{
	switch (key) {
    case GLUT_KEY_PAGE_UP:
        display_rotate_yaw(1);
        break;
    case GLUT_KEY_PAGE_DOWN:
        display_rotate_yaw(-1);
        break;
    case GLUT_KEY_LEFT:
        display_rotate_pitch(-1);
        break;
    case GLUT_KEY_RIGHT:
        display_rotate_pitch(1);
        break;
    case GLUT_KEY_UP:
        display_rotate_roll(1);
        break;
    case GLUT_KEY_DOWN:
        display_rotate_roll(-1);
        break;
	}

    glutPostRedisplay();
}

void callback_setup()
{
    glutDisplayFunc(callback_display);
    glutKeyboardFunc(callback_keyboard);
    glutSpecialFunc(callback_special);
}

