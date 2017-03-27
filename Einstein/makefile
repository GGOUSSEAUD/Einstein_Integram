CC=gcc
SRC=corps.c affiche.c main.c
OBJ=$(SRC:.c=.o)
FLAGS=-Wall -g

fil:  $(OBJ) lib.h
	$(CC) -o $@ $^

%.o:	%.c
	$(CC) -c $< $(FLAGS)

clean:
	rm *.o *~ core

