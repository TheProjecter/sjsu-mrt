#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "glut.h"
#include "texture.h"

static float granite[TEXTURE_SIZE][TEXTURE_SIZE][TEXTURE_SIZE][3];
static float marble[TEXTURE_SIZE][TEXTURE_SIZE][TEXTURE_SIZE][3];

/* holds random values in range [0, 1) */
static double noise[NOISE_SIZE][NOISE_SIZE][NOISE_SIZE];

/* texture IDs */
static GLuint tex[2];

static void generate_noise()
{
    srand(time(NULL));
    for (int x = 0; x < 16; x++)
        for (int y = 0; y < 16; y++)
            for (int z = 0; z < 16; z++)
                noise[x][y][z] = rand() % RAND_MAX / (double) RAND_MAX;
}

static double terp(double x, double y, double z)
{
   /* the fractional part of the given coordinates */
   double frac_x = x - (int) x;
   double frac_y = y - (int) y;
   double frac_z = z - (int) z;

   /* wrap around */
   int x1 = ((int) x + NOISE_SIZE) % NOISE_SIZE;
   int y1 = ((int) y + NOISE_SIZE) % NOISE_SIZE;
   int z1 = ((int) z + NOISE_SIZE) % NOISE_SIZE;

   /* neighbors ahead */
   int x2 = (x1 + NOISE_SIZE + 1) % NOISE_SIZE;
   int y2 = (y1 + NOISE_SIZE + 1) % NOISE_SIZE;
   int z2 = (z1 + NOISE_SIZE + 1) % NOISE_SIZE;

   /* smooth the noise with trilinear interpolation */
   double value = 0;
   value += frac_x       * frac_y       * frac_z       * noise[x2][y2][z2];
   value += (1 - frac_x) * frac_y       * frac_z       * noise[x1][y2][z2];
   value += frac_x       * (1 - frac_y) * frac_z       * noise[x2][y1][z2];
   value += frac_x       * frac_y       * (1 - frac_z) * noise[x2][y2][z1];
   value += (1 - frac_x) * (1 - frac_y) * frac_z       * noise[x1][y1][z2];
   value += frac_x       * (1 - frac_y) * (1 - frac_z) * noise[x2][y1][z1];
   value += (1 - frac_x) * frac_y       * (1 - frac_z) * noise[x1][y2][z1];
   value += (1 - frac_x) * (1 - frac_y) * (1 - frac_z) * noise[x1][y1][z1];
   return value;
}

static double turbulence(double s, double x, double y, double z)
{
    double sum = 0;

    for (double size = s; size >= 1; size /= 2)
        sum += terp(x / size, y / size, z / size) * size;

    return sum / s;
}

static void generate_granite()
{
    for (int x = 0; x < TEXTURE_SIZE; x++)
        for (int y = 0; y < TEXTURE_SIZE; y++)
            for (int z = 0; z < TEXTURE_SIZE; z++) {
                double t = turbulence(4, x, y, z);
                granite[x][y][z][0] = t * 0.5;
                granite[x][y][z][1] = t * 0.5;
                granite[x][y][z][2] = t * 0.5;
            }
}

static double undulate(double v)
{
    return v < 0.5 ? 2 - v : v;
}

static void generate_marble()
{
    double a = 6, s = 64;

    for (int x = 0; x < TEXTURE_SIZE; x++)
        for (int y = 0; y < TEXTURE_SIZE; y++)
            for (int z = 0; z < TEXTURE_SIZE; z++) {
                double t = s + a * turbulence(s, x, y, z);
                double m = undulate(fabs(sin(t * PI)));

                marble[x][y][z][0] = m * 0.5;
                marble[x][y][z][1] = m * 0.9;
                marble[x][y][z][2] = m;
            }
}

static void set_none()
{
    glBindTexture(GL_TEXTURE_3D, 0);
}

static void set_granite()
{
    glBindTexture(GL_TEXTURE_3D, tex[0]);
}

static void set_marble()
{
    glBindTexture(GL_TEXTURE_3D, tex[1]);
}

void texture_select()
{
    static int counter = 0;

    switch (counter % 3) {
    case 0:
        set_granite();
        break;
    case 1:
        set_marble();
        break;
    case 2:
        set_none();
        break;
    }

    counter++;
}

void texture_setup()
{
    generate_noise();
    generate_granite();
    generate_marble();

    glGenTextures(2, tex);

    /* granite texture */
    glBindTexture(GL_TEXTURE_3D, tex[0]);
    glTexImage3D(GL_TEXTURE_3D, 0, GL_RGB,
                 TEXTURE_SIZE, TEXTURE_SIZE, TEXTURE_SIZE,
                 0, GL_RGB, GL_FLOAT, granite);

    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    /* marble texture */
    glBindTexture(GL_TEXTURE_3D, tex[1]);
    glTexImage3D(GL_TEXTURE_3D, 0, GL_RGB,
                 TEXTURE_SIZE, TEXTURE_SIZE, TEXTURE_SIZE,
                 0, GL_RGB, GL_FLOAT, marble);

    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    /* no texture */
    glBindTexture(GL_TEXTURE_3D, 0);
}

