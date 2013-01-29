CC = gcc
CFLAGS = -lm -g -O2
OBJECTS = rps.o

main.exe : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o RockPaperScissors

%.o : %.c
	$(CC) $(CFLAGS) -c $<
