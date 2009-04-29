/*
 * Load the Stanford bunny that's in the PLY file format.
 *
 * bunny.ply is available at:
 * http://graphics.stanford.edu/data/3Dscanrep/
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "display.h"
#include "ply.h"

static void skip_header(FILE *file)
{
    char buffer[80];

    do {
        char *p = fgets(buffer, 80, file);

        if (p == NULL)
            puts("skip_header(): fgets error");
    } while (strcmp(buffer, "end_header\n") != 0);
}

static void load_vertices(FILE *file)
{
    char buffer[80];

    for (int i = 0; i < NUM_VERTICES; i++) {
        char *p = fgets(buffer, 80, file);

        if (p == NULL)
            puts("load_vertices(): fgets error");

        sscanf(buffer, "%f %f %f", &vert[i][0], &vert[i][1], &vert[i][2]);
    }
}

static void load_faces(FILE *file)
{
    for (int i = 0; i < NUM_FACES; i++) {
        int v = fscanf(file, "3 %d %d %d\n",
                       &faces[i][0], &faces[i][1], &faces[i][2]);

        if (v == EOF)
            perror("bunny");
    }
}

void ply_load_mesh()
{
    FILE *file = fopen(MESH_FILENAME, "r");

    if (file == NULL) {
        perror("ply_load_mesh()");
        exit(EXIT_FAILURE);
    }

    skip_header(file);
    load_vertices(file);
    load_faces(file);
}

