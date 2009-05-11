#include <math.h>
#include <GL/glut.h>
#include "ply.h"
#include "vector.h"
#include "display.h"

float vert[NUM_VERTICES][3];
int faces[NUM_FACES][3];

static float norm[NUM_VERTICES][3];

static GLuint bunny;

static void get_normal(int i, int j, int k, float *n)
{
    float first[3], second[3];
    vector_sub(vert[j], vert[i], first);
    vector_sub(vert[k], vert[i], second);
    vector_cross(first, second, n);
    vector_normalize(n);
}

static void draw_objects()
{
    glCallList(bunny);

    glPushMatrix();
    glTranslatef(-5, 2, -10);
    glColor3f(0.5, 0.5, 0.5);
    glutSolidSphere(5, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glRotatef(270, 0, 1, 0);
    glTranslatef(0, -5, 20);
    glColor3f(1, 1, 1);
    glutSolidTeapot(4);
    glPopMatrix();
}

void display_draw()
{
    glMatrixMode(GL_MODELVIEW);

    draw_objects();
}

void display_init()
{
    int i, j;

    ply_load_mesh();

    for (i = 0; i < NUM_FACES; i++) {
        int *v = faces[i];
        float vn[3];

        get_normal(v[0], v[1], v[2], vn); /* normal of the triangle face */
        for (j = 0; j < 3; j++) {
            int index = v[j];

            /* add face normals to vertex normals */
            vector_add(vn, norm[index], norm[index]);
        }
    }

    bunny = glGenLists(1);
    glNewList(bunny, GL_COMPILE);

    glPushMatrix();
    glLoadIdentity();
    glScalef(16, 16, 16);

    glColor3ub(92, 64, 55);
    glBegin(GL_TRIANGLES);
    for (i = 0; i < NUM_FACES; i++)
        for (j = 0; j < 3; j++) {
            int vindex = faces[i][j];

            glNormal3fv(norm[vindex]);
            glVertex3fv(vert[vindex]);
        }
    glEnd();

    glPopMatrix();
    glEndList();
}

