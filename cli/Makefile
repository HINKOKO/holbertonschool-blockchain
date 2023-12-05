CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -Wno-deprecated-declarations -std=gnu90 -ggdb3 -c -I. -I../blockchain/v0.3/ -I../blockchain/v0.3/transaction/ -I../blockchain/v0.3/provided -I../crypto
LIBS = -L../blockchain/v0.3 -lhblk_blockchain -L../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
BIN = cli

clean:
	$(RM) *~ $(BIN)

oclean:
	$(RM) $(OBJ)

fclean: oclean clean

cli: cli.h $(OBJ)
	$(CC) $(OBJ) -o $(BIN) $(LIBS)
