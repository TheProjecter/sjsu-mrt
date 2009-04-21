#include "glut.h"
#include "main.h"
#include "perspective.h"

static float x = 0.8, y = 0.9, z = 0.8;
static float lx = -1, ly = -1, lz = -1;

static void position_camera()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(15, WIDTH / HEIGHT, 1, 1000);
    gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0, 1, 0);
}

void perspective_move(int direction)
{
    x += direction * lx * 0.03;
    y += direction * ly * 0.03;
    z += direction * lz * 0.03;
    position_camera();
}

void perspective_setup()
{
    glViewport(0, 0, WIDTH, HEIGHT);
    position_camera();
}

