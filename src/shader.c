#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include "shader.h"

/* shaders */
GLhandleARB shader_main;
GLhandleARB shader_cel_shading;
static GLhandleARB frag_lighting;

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

void shader_select()
{
    static int counter = 0;

    switch (counter % 2) {
    case 0:
        shader_main = 0;
        break;
    case 1:
        shader_main = frag_lighting;
        break;
    }

    glUseProgramObjectARB(shader_main);
    counter++;
}

void shader_init()
{
    glewInit();

    shader_load(&frag_lighting, "frag-lighting");
    shader_load(&shader_cel_shading, "cel-shading");

    shader_main = frag_lighting;
    glUseProgramObjectARB(shader_main);
}

