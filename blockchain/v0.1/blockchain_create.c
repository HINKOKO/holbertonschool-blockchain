#include "blockchain.h"

block_t const _genesis = {
	{
		/* info */
		0 /* index */,
		0,			/* difficulty */
		1537578000, /* timestamp */
		0,			/* nonce */
		{0}			/* prev_hash */
	},
	{
		/* data */
		"Holberton School", /* buffer */
		16					/* len */
	},
	"\xc5\x2c\x26\xc8\xb5\x46\x16\x39\x63\x5d\x8e\xdf\x2a\x97\xd4\x8d"
	"\x0c\x8e\x00\x09\xc8\x17\xf2\xb1\xd3\xd7\xff\x2f\x04\x51\x58\x03"
	/* 'pure' hash without escape slash is */
	/* c52c26c8b5461639635d8edf2a97d48d0c8e0009c817f2b1d3d7ff2f04515803 */
};

/**
 * blockchain_create - Creates a Blockchain struct, initialize it.
 * Must contain one block upon creation
 *
 * Return: pointer to Blockchain struct which has been initialzed
 */

blockchain_t *blockchain_create(void)
{
	blockchain_t *new_bchain = NULL;
	block_t *block = NULL;
	llist_t *list = NULL;

	list = llist_create(MT_SUPPORT_TRUE);

	block = calloc(1, sizeof(*block));
	new_bchain = calloc(1, sizeof(*new_bchain));
	if (!new_bchain || !block || !list)
	{
		free(new_bchain), free(block);
		llist_destroy(list, 1, NULL);
		return (NULL);
	}
	block->info.index = _genesis.info.index;
	block->info.difficulty = _genesis.info.difficulty;
	block->info.timestamp = _genesis.info.timestamp;
	block->info.nonce = _genesis.info.nonce;

	memcpy(&(block->data.buffer), _genesis.data.buffer, _genesis.data.len);
	block->data.len = _genesis.data.len;
	memcpy(&(block->hash), _genesis.hash, SHA256_DIGEST_LENGTH);

	if (llist_add_node(list, (llist_node_t *)block, ADD_NODE_FRONT) != 0)
	{
		free(new_bchain), free(block);
		llist_destroy(list, 1, NULL);
		return (NULL);
	}
	new_bchain->chain = list;
	return (new_bchain);
}
