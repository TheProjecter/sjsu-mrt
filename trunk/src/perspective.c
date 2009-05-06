#include <math.h>
#include <stdio.h>
#include <GL/glut.h>
#include "main.h"
#include "perspective.h"

/*
 * phi is the angle from the y-axis
 * theta is the angle from the z-axis
 */
float phi = 1.99;
float theta = -1.04;

static float x = 17.16;
static float y = 12.08;
static float z = 11.35;

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

