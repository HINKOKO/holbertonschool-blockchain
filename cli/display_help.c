#include "cli.h"

#define CMD "\033[33m"
#define MSG "\033[34m"
#define RESET "\033[0m"

/**
 *
 *
 */

int cli_docs(bc_t **bc, block_t **active, EC_KEY **key, char *arg1, char *arg2)
{
	printf("\n%s**********CLI MAN PAGE************%s\n", MSG, RESET);
	printf("Available commands are:\n");
	printf("%s\twallet_load <path>%s\n\t\tLoads a wallet from a path file or folder containing pair of EC KEY\n", CMD, RESET);
	printf("%s\twallet_save <path>%s\n\t\t Saves key-pair (string) to the folder given as path\n", CMD, RESET);
	printf("%s\t send <amount> <address>%s\n\t\tSend amount coins to address\n", CMD, RESET);
	printf("%s\t help%s\n\t\tDisplay this help page\n", CMD, RESET);
	return (0);
	(void)bc;
	(void)active;
	(void)key;
	(void)arg1;
	(void)arg2;
}
