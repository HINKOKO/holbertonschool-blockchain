#include <stdio.h>
#include <stdlib.h>

#include "../blockchain.h"

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS||FAILURE
 */

int main(void)
{
	blockchain_t *blockchain;
	block_t *first, *block;

	blockchain = blockchain_create();
	first = llist_get_head(blockchain->chain);

	block = block_create(first, (int8_t *)"Holberton", 9);
	block_hash(block, block->hash);
	llist_add_node(blockchain->chain, block, ADD_NODE_REAR);

	if (block_is_valid(first, NULL) != 0 ||
		block_is_valid(block, first) != 0)
	{
		fprintf(stderr, "Invalid Block\n");
		return (EXIT_FAILURE);
	}
	printf("Blockchain is Valid dude!\n");
	blockchain_destroy(blockchain);

	return (EXIT_SUCCESS);
}
