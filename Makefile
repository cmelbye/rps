MAIN=rps
CFLAGS=-ansi -Wall -pedantic -lm

all: debug run

debug : ${MAIN}_debug
run : ${MAIN}_run

${MAIN}_debug : ${MAIN}.c checkit.h
	gcc -o ${MAIN}_debug ${CFLAGS} ${MAIN}.c

${MAIN}_run : ${MAIN}.c checkit.h
	gcc -o ${MAIN}_run -DNCHECKIT ${CFLAGS} ${MAIN}.c

clean :
	\rm ${MAIN}_debug ${MAIN}_run

