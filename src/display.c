#include <math.h>
#include <GL/glut.h>
#include "ply.h"
#include "vector.h"
#include "display.h"

float vert[NUM_VERTICES][3];
int faces[NUM_FACES][3];

static float norm[NUM_VERTICES][3];
static float tex[NUM_VERTICES][3];

static void get_normal(int i, int j, int k, float *n)
{
    float first[3], second[3];
    vector_sub(vert[j], vert[i], first);
    vector_sub(vert[k], vert[i], second);
    vector_cross(first, second, n);
    vector_normalize(n);
}

void display_draw()
{
    int i, j;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glScalef(2, 2, 2);

    glColor3f(1, 1, 1);
    glBegin(GL_TRIANGLES);
    for (i = 0; i < NUM_FACES; i++)
        for (j = 0; j < 3; j++) {
            int vindex = faces[i][j];

            glNormal3fv(norm[vindex]);
            glTexCoord3fv(tex[vindex]);
            glVertex3fv(vert[vindex]);
        }
    glEnd();
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

    for (i = 0; i < NUM_VERTICES; i++) {
        /*vector_normalize(norm[i]);*/

        for (j = 0; j < 3; j++)
            tex[i][j] = vert[i][j] * 10 + 1;
    }
}

