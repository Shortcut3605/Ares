CC = gcc
CFLAGS = -c -std=c99 -g
LDFLAGS = -g
SRC =  $(wildcard src/*.c)
HDR = $(wildcard src/include/*.h)
OBJ = ${SRC:.c=.o}
EXEC = ares

all: ${SRC} ${OBJ} ${EXEC}

${EXEC}: ${OBJ}
	${CC} ${LDFLAGS} $^ -o $@

%.o: %.c ${HDR}
	${CC} ${CFLAGS} $< -o $@
clean:
	rm src/*.o
	rm ${EXEC}
