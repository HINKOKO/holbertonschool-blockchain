CC=gcc
FLAGS=-Wall -Wextra -Werror -pedantic -Wno-deprecated-declarations -g3 -I. -Itransaction/ -Iprovided/ -I../../crypto -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread

SRCLIB= $(wildcard *.c) $(wildcard transaction/*.c) $(wildcard provided/*.c)
OBJLIB= $(SRCLIB:.c=.o)
LIBNAME=libhblk_blockchain.a

.PHONY: clean oclean fclean libhblk_blockchain.a

clean:
	$(RM) *~ $(LIBNAME)

oclean:
	$(RM) $(OBJLIB)

fclean: clean oclean

libhblk_blockchain.a: blockchain.h transaction/transaction.h $(OBJLIB)
	ar rcs $(LIBNAME) $(OBJ0)
