CC=gcc
FLAGS=-Wall -Wextra -Werror -pedantic -g3 -I. -Itransaction/ -Iprovided/ -I../../crypto -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread

SRCLIB= $(wildcard *.c) $(wildcard transaction/*.c) $(wildcard provided/*.c)
OBJLIB= $(SRCLIB:.c=.o)
HDRS = blockchain.h transaction/transaction.h
LIBNAME=libhblk_blockchain.a

libhblk_blockchain.a: $(HDRS) $(OBJLIB)
	ar rcs $(LIBNAME) $(OBJ0)
