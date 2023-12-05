#include "cli.h"

/**
 * wallet_save - Saves a Wallet on DISK
 *
 */

int cmd_wallet_save(bc_t **bc, block_t **active, EC_KEY **key, char *arg1, char *arg2)
{
	if (!arg1)
	{
		fprintf(stderr, "Usage: wallet_save <path>\n");
		return (0);
	}
	if (ec_save(*key, arg1) != 1)
	{
		fprintf(stderr, "Error saving key to %s\n", arg1);
		return (0);
	}
	printf("U'r wallet was saved successfully\n");
	return (1);
	(void)arg2;
	(void)active;
	(void)bc;
}
