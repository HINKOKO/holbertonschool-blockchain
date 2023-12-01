CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -Wno-deprecated-declarations -std=gnu90 -ggdb3 -c -I. -Itransaction/ -Iprovided/ -I../../crypto -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread

SRC_ALL = $(wildcard *.c) $(wildcard transaction/*.c) $(wildcard provided/*.c)
OBJ_ALL = $(SRC_ALL:.c=.o)

SRC_PROVIDED = $(wildcard provided/*.c)
OBJ_PROVIDED = $(notdir $(SRC_PROVIDED:.c=.o))

OBJ0 = $(filter-out $(OBJ_PROVIDED), $(OBJ_ALL))
NAME0 = libhblk_blockchain.a

.PHONY: clean oclean fclean libhblk_blockchain.a

clean:
	$(RM) *~ $(NAME0)

oclean:
	$(RM) $(OBJ0) transaction/*.o

fclean: clean oclean
	$(RM) provided/*.o

libhblk_blockchain.a: blockchain.h transaction/transaction.h $(OBJ0)
	ar rcs $(NAME0) $(OBJ0)
