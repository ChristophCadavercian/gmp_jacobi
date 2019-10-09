CC = gcc
CFLAGS = -lgmp -O
OBJS = ./src/main.c
main: $(OBJS)
	$(CC) $(CFLAGS) -o elliptic_kurwa $(OBJS)
clean:
	rm  elliptic_kurwa
