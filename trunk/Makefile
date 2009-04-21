target = shader
objects = $(patsubst %.c,%.o,$(wildcard src/*.c))

CC = gcc
CFLAGS = -std=c99 -Wall -O2 -I/usr/include/GL
LDFLAGS = -lm -lglut -lGLU -lGL

$(target):	$(objects)
		$(CC) $(LDFLAGS) $^ -o $@

.PHONY:	clean
clean:
		$(RM) $(target) $(objects)

