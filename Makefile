CFLAGS = -g -fsanitize=address -Wall

all: calculator

calculator: *.c
	${CC} ${CFLAGS} -o $@ $^
