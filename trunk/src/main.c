#include "glut.h"
#include "display.h"
#include "callback.h"
#include "perspective.h"
#include "shader.h"
#include "texture.h"
#include "main.h"

static void lighting_init()
{
    float amb[] = { 0.1, 0.1, 0.1, 1 };
    float diff[] = { 1, 1, 1, 1 };
    float pos[] = { 500, 100, -100, 1 };
    float dir[] = { -1, 0, 0 };

    glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45);

    glEnable(GL_LIGHT0);
}

int main(int argc, char *argv[])
{
    glutInitWindowPosition(POS_X, POS_Y);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow(TITLE);
    glClearColor(0, 0, 0, 1);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_3D);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    callback_init();
    perspective_init();
    lighting_init();
    texture_init();
    display_init();
    shader_init();

    glutMainLoop();
    return 0;
}

