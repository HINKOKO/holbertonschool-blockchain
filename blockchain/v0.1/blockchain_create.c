#include "blockchain.h"

#include <./provided/_genesis.c>

/**
 * blockchain_create - Creates a Blockchain struct, initialize it.
 * Must contain one block upon creation
 *
 * Return: pointer to Blockchain struct which has been initialzed
 */

blockchain_t *blockchain_create(void)
{
	blockchain_t *new_blockchain = NULL;
	block_t *gen = NULL;
	llist_t *list = NULL;

	new_blockchain = calloc(1, sizeof(*new_blockchain));
	gen = calloc(1, sizeof(*gen));
	/* Example compiled with '-pthread' -> we enable multithreading */
	list = llist_create(MT_SUPPORT_TRUE);

	if (!new_blockchain || !gen || !list)
		return (NULL);

	gen->info.index = _genesis.info.index;
	gen->info.timestamp = _genesis.info.timestamp;
	gen->info.nonce = _genesis.info.nonce;
	memcpy(&(gen->data.buffer), _genesis.data.buffer, _genesis.data.len);
	memcpy(&(gen->hash), _genesis.hash, SHA_DIGEST_LENGTH);

	if (llist_add_node(list, gen, ADD_NODE_FRONT) != 0)
	{
		free(gen), free(new_blockchain);
		llist_destroy(list, 1, NULL);
		return (NULL);
	}
	new_blockchain->chain = list;
	return (new_blockchain);
}
