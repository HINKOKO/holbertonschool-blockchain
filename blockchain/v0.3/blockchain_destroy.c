#include "blockchain.h"

/**
 * blockchain_destroy - deletes an existing Blockchain,
 * along with all the blocks it contains
 * @blockchain: pointer to the Blockchain struct to wipe out
 *
 */

void blockchain_destroy(blockchain_t *blockchain)
{
	if (!blockchain)
		return;

	llist_destroy(blockchain->unspent, 1, (node_dtor_t)block_destroy);
	llist_destroy(blockchain->chain, 1, NULL);
	free(blockchain);
}
