#include "cli.h"

/**
 * check_builtins - Takes a string `cmd` as argument
 * and iterates through the bucket array of available built-in
 * @cmd: >Pointer to char array (string)
 * --> the `command` argument (coming from CLI)
 * Return: Pointer to corresponding function which handles the command
 * --> Functions with signatures as
 * int (*f)(bc_t **, block_t **, EC_KEY **, char *, char *)
 *
 */

int (*check_builtin(char *cmd))(bc_t **, block_t **, EC_KEY **, char *, char *)
{
	int i;
	built_in_t bucket[] = {
		{"wallet_load", &cmd_wallet_load},
		{"help", &cli_docs},
		{"wallet_save", &cmd_wallet_save},
		{"send", &cmd_send_coins},
		{NULL, NULL},
		/*{"mine", &mine_a_block},
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
