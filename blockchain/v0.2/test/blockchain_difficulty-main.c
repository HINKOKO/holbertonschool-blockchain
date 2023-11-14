#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../blockchain.h"

void _blockchain_print_brief(blockchain_t *blockchain);

/**
 * _add_block - adds a block to the wonderful Bchain
 * @bchain: the bchain to add blocks on
 * @prev: prev (last) block in the chain
 * @s: the content to store in new block
 * Return: pointer to the newly created block
 */

static void *_add_block(blockchain_t *bchain, block_t const *prev,
						char const *s)
{
	block_t *block;

	usleep(300000); /* Simulate block mining... */
	printf("\tMining process..\n");
	fflush(stdout);

	block = block_create(prev, (int8_t *)s, (uint32_t)strlen(s));

	block->info.difficulty = blockchain_difficulty(bchain);
	block_hash(block, block->hash);
	llist_add_node(bchain->chain, block, ADD_NODE_REAR);

	return (block);
}

/**
 * main - entry point
 * Return: always success
 */

int main(void)
{
	blockchain_t *bchain;
	block_t *block;

	bchain = blockchain_create();
	block = llist_get_head(bchain->chain);
	block = _add_block(bchain, block, "Holberton");
	block = _add_block(bchain, block, "School");
	block = _add_block(bchain, block, "of");
	block = _add_block(bchain, block, "Software");
	block = _add_block(bchain, block, "Engineering");
	block = _add_block(bchain, block, "972");
	block = _add_block(bchain, block, "Mission");
	block = _add_block(bchain, block, "Street");
	block = _add_block(bchain, block, "San Francisco");
	block = _add_block(bchain, block, "CA");
	block = _add_block(bchain, block, "CA");
	block = _add_block(bchain, block, "\\o/");

	_blockchain_print_brief(bchain);

	/* Noooo don't do this !! */
	blockchain_destroy(bchain);

	return (EXIT_SUCCESS);
}
