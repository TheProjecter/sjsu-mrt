#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include "shader.h"

/* shaders */
GLhandleARB shader_main;
static GLhandleARB frag_light, negative;

static void glsl_read(GLhandleARB shader, char *filename)
{
    char *content;
    long count;
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("glsl_read()");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    count = ftell(file);
    count++;
    rewind(file);

    if (count <= 1) {
        puts("error: shader file is empty");
        exit(EXIT_FAILURE);
    }

    content = malloc(count * sizeof(char));
    count = fread(content, sizeof(char), count, file);
    content[count] = '\0';

    glShaderSourceARB(shader, 1, (const char **) &content, NULL);

    free(content);
    fclose(file);
}

static void print_info_log(GLhandleARB obj)
{
    int length, written;
    char *info_log;

    glGetObjectParameterivARB(obj, GL_OBJECT_INFO_LOG_LENGTH_ARB, &length);
    if (length <= 0)
        return;

    info_log = malloc(length * sizeof(char));
    glGetInfoLogARB(obj, length, &written, info_log);
    info_log[written] = '\0';
    printf("%s\n", info_log);

    free(info_log);
}

static void shader_load(GLhandleARB *shader, char *name)
{
    GLhandleARB vert, frag;
    char filename[80];

    vert = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
    frag = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);

    sprintf(filename, "shaders/%s.vert.glsl", name);
    glsl_read(vert, filename);
    sprintf(filename, "shaders/%s.frag.glsl", name);
    glsl_read(frag, filename);

    glCompileShaderARB(vert);
    glCompileShaderARB(frag);
    print_info_log(vert);
    print_info_log(frag);

    *shader = glCreateProgramObjectARB();
    glAttachObjectARB(*shader, vert);
    glAttachObjectARB(*shader, frag);

    glLinkProgramARB(*shader);
    print_info_log(*shader);
}

#if 0
void shader_select()
{
    static int counter = 1;

    switch (counter % 3) {
    case 0:
        glUseProgramObjectARB(0);
        break;
    case 1:
        glUseProgramObjectARB(frag_light);
        break;
    case 2:
        glUseProgramObjectARB(negative);
        break;
    }

    counter++;
}
#endif

void shader_init()
{
    glewInit();

    shader_load(&frag_light, "frag-lighting");
    shader_load(&negative, "negative");

    shader_main = frag_light;
    glUseProgramObjectARB(shader_main);
}

