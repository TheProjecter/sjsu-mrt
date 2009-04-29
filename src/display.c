#include <math.h>
#include "glut.h"
#include "ply.h"
#include "display.h"

float vert[NUM_VERTICES][3];
int faces[NUM_FACES][3];

static float norm[NUM_VERTICES][3];
static float tex[NUM_VERTICES][3];

/* rotation controls */
static int yaw, pitch, roll;

static void normalize(float *v)
{
    float length = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    v[0] /= length;
    v[1] /= length;
    v[2] /= length;
}

static void vector(int a, int b, float *v)
{
    v[0] = vert[a][0] - vert[b][0];
    v[1] = vert[a][1] - vert[b][1];
    v[2] = vert[a][2] - vert[b][2];
}

static void cross_product(float *a, float *b, float *result)
{
    result[0] = a[1] * b[2] - b[1] * a[2];
    result[1] = a[2] * b[0] - b[2] * a[0];
    result[2] = a[0] * b[1] - b[0] * a[1];
}

static void normal(int i, int j, int k, float *n)
{
    float first[3], second[3];
    vector(j, i, first);
    vector(k, i, second);
    cross_product(first, second, n);
    normalize(n);
}

static void vector_add(float *n, int index)
{
    norm[index][0] += n[0];
    norm[index][1] += n[1];
    norm[index][2] += n[2];
}

void display_rotate_reset()
{
    yaw = 0;
    pitch = 0;
    roll = 0;
}

void display_rotate_yaw(int direction)
{
    yaw += direction;
}

void display_rotate_pitch(int direction)
{
    pitch += direction;
}

void display_rotate_roll(int direction)
{
    roll += direction;
}

void display_draw()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(yaw, 0, 0, 1);
    glRotatef(pitch, 0, 1, 0);
    glRotatef(roll, 1, 0, 0);

    glColor3f(1, 1, 1);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < NUM_FACES; i++)
        for (int j = 0; j < 3; j++) {
            int vindex = faces[i][j];

            glNormal3fv(norm[vindex]);
            glTexCoord3fv(tex[vindex]);
            glVertex3fv(vert[vindex]);
        }
    glEnd();
}

void display_init()
{
    ply_load_mesh();

    for (int i = 0; i < NUM_FACES; i++) {
        int *v = faces[i];
        float vn[3];

        normal(v[0], v[1], v[2], vn); /* normal of the triangle face */
        for (int j = 0; j < 3; j++)
            vector_add(vn, v[j]); /* add face normals to vertex normals */
    }

    for (int i = 0; i < NUM_VERTICES; i++) {
        normalize(norm[i]);

        for (int j = 0; j < 3; j++)
            tex[i][j] = vert[i][j] * 10 + 1;
    }
}

