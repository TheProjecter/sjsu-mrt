#include <math.h>
#include <stdio.h>
#include <GL/glut.h>
#include "main.h"
#include "perspective.h"

/*
 * phi is the angle from the y-axis
 * theta is the angle from the z-axis
 */
float phi, theta;

static float x, y, z;
static float lx, ly, lz;

static void turn_camera(float p, float t)
{
    /* take advantage of the spherical coordinate system */
    lx = sin(p) * sin(t);
    ly = cos(p);
    lz = sin(p) * cos(t) * -1;
}

static void position_camera()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, WIDTH / HEIGHT, 1, 1000);
    gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0, 1, 0);
}

void perspective_load()
{
    phi = 2.12;
    theta = -0.97;
    x = 0.8;
    y = 0.9;
    z = 0.8;

    turn_camera(phi, theta);
    position_camera();
}

void perspective_print()
{
    printf("location = (%.2f, %.2f, %.2f)\n", x, y, z);
    printf("direction = (%.2f, %.2f, %.2f)\n", lx, ly, lz);
    printf("phi = %.2f, theta = %.2f\n", phi, theta);
    printf("--\n");
}

void perspective_strafe(int direction)
{
    turn_camera(phi, theta + M_PI_2);
    x += direction * lx * 2.5;
    z += direction * lz * 2.5;
    turn_camera(phi, theta);

    position_camera();
}

void perspective_move(int direction)
{
    x += direction * lx * 2.5;
    y += direction * ly * 2.5;
    z += direction * lz * 2.5;
    position_camera();
}

void perspective_turn(float p, float t)
{
    turn_camera(p, t);
    position_camera();
}

void perspective_init()
{
    glViewport(0, 0, WIDTH, HEIGHT);
    perspective_load();
}

