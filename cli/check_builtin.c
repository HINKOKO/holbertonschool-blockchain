#include "cli.h"

/**
 * check_builtins - Check if input match any CLI builtins
 *
 */

int (*check_builtin(char *cmd))(bc_t **, block_t **, EC_KEY **, char *, char *)
{
	int i;
	built_in_t bucket[] = {
		{"wallet_load", &cmd_wallet_load},
		{"help", &cli_docs},
		{"wallet_save", &cmd_wallet_save},
		{NULL, NULL},
		/* {"send", &send_amount_addr},
		{"mine", &mine_a_block},
		{"exit", &_exit}, */
	};

	if (!cmd)
		return (NULL);

	for (i = 0; bucket[i].cmd != NULL; i++)
	{
		if (strcmp(cmd, bucket[i].cmd) == 0)
			return (bucket[i].f);
	}
	return (NULL);
}
