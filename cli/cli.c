#include "cli.h"

#define CMD "\033[31m"
#define RESET "\033[0m"
#define EC_COMP 33

void ec_compressed(EC_KEY *key, uint8_t pub[EC_COMP]);

/**
 * generate_default_key - At CLI start-up, generate a default
 * EC_KEY pair for future use (In case User do not have keys on its disk)
 * Return: The default wallet
 */

EC_KEY *generate_default_key()
{
	EC_KEY *default_wallet;

	default_wallet = ec_create();
	ec_save(default_wallet, "./beta");
	return (default_wallet);
}

/**
 * handle_the_load - 'Helper' function that will load
 * the default-Key generated by CLI startup, in case User
 * do not have a Key-Pair on the Disk
 * Return: An EC_KEY pair struct ready to go
 */

EC_KEY *handle_the_load()
{
	EC_KEY *out;
	char choice;

	printf("Usage: wallet_load <path>\n");
	printf("%sNote that the CLI loaded by default", CMD);
	printf("key-pair in folder `beta`%s\n", RESET);
	printf("\tPress %s1%s for using default\n", CMD, RESET);
	printf("\tPress %s2%s to go back to home\n", CMD, RESET);

	scanf(" %c", &choice);
	getchar();

	/* Load default that was generated */
	if (choice == '1')
	{
		out = generate_default_key();
		printf("Wallet loaded successfully - PubKey (from default folder) => ");
	}
	if (choice == '2')
		return (NULL);
	printf("Invalid choice\n");

	return (out);
}

/**
 * main - Entry point of CLI
 * Return: EXIT_SUCCESS||FAILURE
 */

int main(void)
{
	EC_KEY *beta, *out;
	uint8_t pub[EC_COMP];
	blockchain_t *bc;
	block_t *active;
	char *line = NULL, *cmd, *arg1, *arg2;
	size_t len;
	ssize_t read;
	int (*func)(blockchain_t **, block_t **, EC_KEY **, char *, char *);

	beta = generate_default_key();
	bc = blockchain_create();
	active = llist_get_head(bc->chain);
	active = block_create(active, (int8_t *)"Blockchainers", 13);

	while (98)
	{
		printf("$holbie_bchain ");
		read = getline(&line, &len, stdin);
		if (read == -1)
			break;
		if (read <= 1)
		{
			free(line);
			continue;
		}
		line = strtok(line, "\n");
		cmd = strtok(line, " ");
		arg1 = strtok(NULL, " ");
		arg2 = strtok(NULL, " ");
		if (!arg1 && strcmp(cmd, "wallet_load") == 0)
		{
			out = handle_the_load();
			if (out)
				ec_compressed(out, pub);
			continue;
		}
		func = check_builtin(cmd);
		if (func)
			func(&bc, &active, &beta, arg1, arg2);
		else
			printf("Unrecognized command, type help for help\n");
	}
	block_destroy(active);
	blockchain_destroy(bc);
	if (line)
		free(line);
	return (0);
}
