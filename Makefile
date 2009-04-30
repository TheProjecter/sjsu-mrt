target = shader
objects = $(patsubst %.c,%.o,$(wildcard src/*.c))

CC = gcc
CFLAGS = -ansi -Wall -O2
LDFLAGS = -lm -lGLEW -lglut -lGLU -lGL

$(target):	$(objects)
		$(CC) $(LDFLAGS) $^ -o $@

.PHONY:	clean
clean:
		$(RM) $(target) $(objects)

