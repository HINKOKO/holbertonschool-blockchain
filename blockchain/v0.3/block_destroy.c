#include "blockchain.h"

/**
 * block_destroy - deletes an existing block
 * @block: points to the block to delete
 * -- Update Insert--
 * Now properly deallocates the Linked lisf of transactions
 * before freeing
 */

void block_destroy(block_t *block)
{
	if (!block)
		return;

	llist_destroy(block->transactions, 1, NULL);
	free(block);
}
