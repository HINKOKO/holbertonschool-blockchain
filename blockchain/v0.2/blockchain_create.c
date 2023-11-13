#include "blockchain.h"

/**
 * init_genesis - helper function to
 * init a genesis block since multi def of _genesis
 * conflict the .rodata section
 * @idx: index of genesis block-MUST be zero
 * Return: pointer to genesis block
 */

block_t *init_genesis(uint32_t idx)
{
	block_t *block;
	char *genesis_data = "Holberton School";
	size_t data_len = strlen((const char *)genesis_data);
	char *hash = "\xc5\x2c\x26\xc8\xb5\x46\x16\x39\x63"
				 "\x5d\x8e\xdf\x2a\x97\xd4\x8d"
				 "\x0c\x8e\x00\x09\xc8\x17\xf2\xb1\xd3\xd7"
				 "\xff\x2f\x04\x51\x58\x03";

	if (idx != 0)
		return (NULL);
	block = calloc(1, sizeof(*block));
	if (!block)
		return (fprintf(stderr, "Unable to edit genesis block"), NULL);

	block->info.index = 0;
	block->info.difficulty = 0;
	block->info.timestamp = 1537578000,
	block->info.nonce = 0;
	memcpy(block->data.buffer, genesis_data, data_len);
	block->data.len = data_len;
	memcpy(block->hash, hash, SHA256_DIGEST_LENGTH);

	return (block);
}

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
	/* Example compiled with '-pthread' -> we enable multithreading */
	list = llist_create(MT_SUPPORT_TRUE);

	if (!new_blockchain || !list)
		return (NULL);

	gen = init_genesis(0);

	if (llist_add_node(list, gen, ADD_NODE_FRONT) != 0)
	{
		free(gen), free(new_blockchain);
		llist_destroy(list, 1, NULL);
		return (NULL);
	}
	new_blockchain->chain = list;
	return (new_blockchain);
}
