CC = gcc
CFLAGS = -lgmp
OBJS = ./src/main.c ./src/jaq_quart.c
main: $(OBJS)
	$(CC) $(CFLAGS) -o elliptic_kurwa $(OBJS)
clean:
	rm  elliptic_kurwa
