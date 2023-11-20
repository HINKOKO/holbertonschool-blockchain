#include "blockchain.h"

/**
 * block_destroy - deletes an existing block
 * @block: points to the block to delete
 */

void block_destroy(block_t *block)
{
	if (!block)
		return;
	free(block);
}
