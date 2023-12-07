#ifndef __HBLK_CLI__
#define __HBLK_CLI__

#define EC_COMP 33
#define TX_POOL 4096

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

typedef struct local_tx
{
	llist_t *tx_pool;
} local_tx_t;

typedef struct bc_data
{
	blockchain_t *bc;
	EC_KEY *key;
	llist_t *tx_pool;
} bc_data_t;

#define BC_INIT          \
	{                    \
		NULL, NULL, NULL \
	}

typedef blockchain_t bc_t;

/**
 * built_in_s - Struct to map command strings
 * to corresponding functions of the CLI
 * @cmd: pointer to string command passed
 * @f: function pointer to corresponding function
 * handling that command
 */

typedef struct built_in_s
{
	char *cmd;
	int (*f)(blockchain_t **, block_t **, EC_KEY **, char *, char *);
} built_in_t;

int (*check_builtin(char *cmd))(bc_t **, block_t **, EC_KEY **, char *, char *);

/* Prototypes for commands handling */
int cmd_wallet_load(bc_t **, block_t **, EC_KEY **, char *, char *);
void ec_compressed(EC_KEY *key, uint8_t pub[EC_COMP]);
int cmd_wallet_save(bc_t **, block_t **, EC_KEY **, char *, char *);
int cmd_send_coins(bc_t **, block_t **, EC_KEY **, char *, char *);

int cli_docs(bc_t **bc, block_t **active, EC_KEY **key, char *arg1, char *arg2);

/* Printers */
void _print_hex_buffer(uint8_t const *buf, size_t len);

#endif /* __HBLK_CLI__ */
