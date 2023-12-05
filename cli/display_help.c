#include "cli.h"

#define CMD "\033[33m"
#define RESET "\033[0m"

/**
 *
 *
 */

int cli_docs(bc_t **bc, block_t **active, EC_KEY **key, char *arg1, char *arg2)
{
	printf("**********CLI MAN PAGE************\n");
	printf("Available commands are:\n");
	printf("%s\twallet_load <path>%s\n\t\tLoads a wallet from a path file or folder containing pair of EC KEY\n", CMD, RESET);
	printf("%s\t help%s\n\t\tDisplay this help page\n", CMD, RESET);
	return (0);
	(void)bc;
	(void)active;
	(void)key;
	(void)arg1;
	(void)arg2;
}
