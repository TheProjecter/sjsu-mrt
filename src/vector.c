#include <math.h>
#include "vector.h"

float vector_magnitude(float v[3])
{
    return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

void vector_normalize(float v[3])
{
    float length = vector_magnitude(v);
    v[0] /= length;
    v[1] /= length;
    v[2] /= length;
}

void vector_add(float v[3], float w[3], float result[3])
{
    result[0] = v[0] + w[0];
    result[1] = v[1] + w[1];
    result[2] = v[2] + w[2];
}

void vector_sub(float v[3], float w[3], float result[3])
{
    result[0] = v[0] - w[0];
    result[1] = v[1] - w[1];
    result[2] = v[2] - w[2];
}

void vector_comp_mult(float v[3], float w[3], float result[3])
{
    result[0] = v[0] * w[0];
    result[1] = v[1] * w[1];
    result[2] = v[2] * w[2];
}

void vector_scalar_mult(float scalar, float v[3], float result[3])
{
    result[0] = scalar * v[0];
    result[1] = scalar * v[1];
    result[2] = scalar * v[2];
}

float vector_dot(float v[3], float w[3])
{
    float sum = 0;
    sum += v[0] * w[0];
    sum += v[1] * w[1];
    sum += v[2] * w[2];
    return sum;
}

void vector_cross(float *v, float *w, float *result)
{
    result[0] = v[1] * w[2] - w[1] * v[2];
    result[1] = v[2] * w[0] - w[2] * v[0];
    result[2] = v[0] * w[1] - w[0] * v[1];
}

