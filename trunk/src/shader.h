#ifndef SHADER_H
#define SHADER_H

void shader_select();
void shader_init();

/* variables of type GLhandleARB */
extern unsigned int shader_main;
extern unsigned int shader_frag_lighting;
extern unsigned int shader_cel_shading;

#endif /* SHADER_H */
