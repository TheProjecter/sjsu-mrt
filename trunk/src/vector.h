#ifndef VECTOR_H
#define VECTOR_H

float vector_magnitude(float v[3]);
void vector_normalize(float v[3]);
void vector_add(float v[3], float w[3], float result[3]);
void vector_sub(float v[3], float w[3], float result[3]);
void vector_comp_mult(float v[3], float w[3], float result[3]);
void vector_scalar_mult(float scalar, float v[3], float result[3]);
float vector_dot(float v[3], float w[3]);
void vector_cross(float *v, float *w, float *result);

#endif /* VECTOR_H */
