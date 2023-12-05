#include "cli.h"

EC_KEY *generate_default_key()
{
	EC_KEY *default_wallet;

	default_wallet = ec_create();
	ec_save(default_wallet, "./beta");
	return (default_wallet);
}

/**
 * main - Entry point
 */

int main(void)
{
	EC_KEY *wallet;
	blockchain_t *bc;
	block_t *active;
	char *line = NULL, *cmd, *arg1, *arg2;
	size_t len;
	int ret, (*func)(blockchain_t **, block_t **, EC_KEY **, char *, char *);

	wallet = generate_default_key();
	bc = blockchain_create();
	active = llist_get_head(bc->chain);
	active = block_create(active, (int8_t *)"Blockchainers", 13);

	while (98)
	{
		printf("$holbie_bchain ");
		if (getline(&line, &len, stdin) == -1)
			break;
		line = strtok(line, "\n");
		cmd = strtok(line, " ");
		arg1 = strtok(NULL, " ");
		arg2 = strtok(NULL, " ");
		func = check_builtin(cmd);
		if (func)
		{
			ret = func(&bc, &active, &wallet, arg1, arg2);
			if (ret == 1)
				continue;
		}
		else
			printf("Unrecognized command, type help for help\n");
	}
	block_destroy(active);
	blockchain_destroy(bc);
	if (line)
		free(line);
	return (0);
}
