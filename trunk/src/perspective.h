#ifndef PERSPECTIVE_H
#define PERSPECTIVE_H

#define M_PI_2  1.57079632679489661923

void perspective_load();
void perspective_print();
void perspective_strafe(int direction);
void perspective_move(int direction);
void perspective_turn(float phi, float theta);
void perspective_init();

extern float phi;
extern float theta;

#endif /* PERSPECTIVE_H */
