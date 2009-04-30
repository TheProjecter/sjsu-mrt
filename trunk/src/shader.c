#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>

/* shaders */
static GLhandleARB green;

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

void shader_select()
{
    static int counter = 0;

    switch (counter % 2) {
    case 0:
        glUseProgramObjectARB(green);
        break;
    case 1:
        glUseProgramObjectARB(0);
        break;
    }

    counter++;
}

void shader_init()
{
    glewInit();

    GLhandleARB vert = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
    GLhandleARB frag = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);

    glsl_read(vert, "shaders/green.vert.glsl");
    glsl_read(frag, "shaders/green.frag.glsl");

    glCompileShaderARB(vert);
    glCompileShaderARB(frag);
    print_info_log(vert);
    print_info_log(frag);

    green = glCreateProgramObjectARB();
    glAttachObjectARB(green, vert);
    glAttachObjectARB(green, frag);

    glLinkProgramARB(green);
    print_info_log(green);
}

