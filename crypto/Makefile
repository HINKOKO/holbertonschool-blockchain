CC=gcc
CFLAGS=-Wall -Wextra -Werror -pedantic -Wno-deprecated-declarations
LIB_FLAGS=-lssl -lcrypto

SRC0:= ec_create.c ec_from_pub.c ec_load.c ec_save.c ec_sign.c ec_to_pub.c ec_verify.c sha256.c
OBJ0 := $(SRC0:.c=.o)
LIB_NAME := libhblk_crypto.a

.PHONY: clean oclean fclean libhblk_crypto.a

clean:
	$(RM) *~ $(LIB_NAME)

oclean:
	$(RM) $(OBJ0)

fclean: clean oclean

# static library maker
libhblk_crypto.a: hblk_crypto.h $(OBJ0)
	ar rcs $(LIB_NAME) $(OBJ0)


