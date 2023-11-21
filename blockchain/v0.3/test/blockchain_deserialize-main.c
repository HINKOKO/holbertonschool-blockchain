#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "blockchain.h"

void _blockchain_print_brief(blockchain_t const *blockchain);

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS||FAILURE
 */

int main(void)
{
	blockchain_t *bchain;

	bchain = blockchain_deserialize("save.hblk");

	_blockchain_print_brief(bchain);
	blockchain_destroy(bchain);

	return (EXIT_SUCCESS);
}
