CC = gcc
CFLAGS = -c -std=c99 -g
LDFLAGS = -g
SRC =  $(wildcard *.c)
HDR = $(wildcard *.h)
OBJ = ${SRC:.c=.o}
EXEC = ares

all: ${SRC} ${OBJ} ${EXEC}

${EXEC}: ${OBJ}
	${CC} ${LDFLAGS} $^ -o $@

%.o: %.c ${HDR}
	${CC} ${CFLAGS} $< -o $@
clean:
	rm *.o
	rm ${EXEC}
