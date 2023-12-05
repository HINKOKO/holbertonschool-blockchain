#ifndef __HBLK_CLI__
#define __HBLK_CLI__

#define EC_COMP 33

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <blockchain.h>
#include <hblk_crypto.h>
#include <transaction.h>

typedef blockchain_t bc_t;

typedef struct built_in_s
{
	char *cmd;
	int (*f)(blockchain_t **, block_t **, EC_KEY **, char *, char *);
} built_in_t;

int (*check_builtin(char *cmd))(bc_t **, block_t **, EC_KEY **, char *, char *);

/* Prototypes for commands handling */
int cmd_wallet_load(bc_t **, block_t **, EC_KEY **, char *, char *);
void ec_compressed(EC_KEY *key, uint8_t pub[EC_COMP]);

int cli_docs(bc_t **bc, block_t **active, EC_KEY **key, char *arg1, char *arg2);

/* Printers */
void _print_hex_buffer(uint8_t const *buf, size_t len);

#endif /* __HBLK_CLI__ */
