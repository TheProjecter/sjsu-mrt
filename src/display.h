#ifndef DISPLAY_H
#define DISPLAY_H

#define NUM_VERTICES    35947
#define NUM_FACES       69451

void display_rotate_reset();
void display_rotate_yaw(int direction);
void display_rotate_pitch(int direction);
void display_rotate_roll(int direction);
void display_draw();
void display_init();

extern float vert[NUM_VERTICES][3];
extern int faces[NUM_FACES][3];

#endif /* DISPLAY_H */
