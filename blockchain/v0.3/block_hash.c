#include "blockchain.h"

/**
 * block_hash - computes the hash of a Block
 * --> we take the sha256 in our crypto/ previous project
 * @block: Points to the block to be hashed
 * @hash_buf: Where to store resulting hash
 *
 * Return: a pointer to hash_buf -> Using the 'sha256()' function
 * from folder 'crypto', function which returns pointer to hash_buf already
 * -- Update v0.3 --
 * Include list of transactions in a Block's hash ----
 * From 1st concept page (about data structures)....
 * Block's hash: will contain a digest of both Block's info and data
 * Here we add the list of transactions.
 *
 */

uint8_t *block_hash(block_t const *block,
					uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{
	/* When hashing a block, we hash info + data */
	/* Now adding the list of transactions */
	size_t full_len = 0, len = sizeof(block->info) + block->data.len;
	int8_t *start, *buf;
	transaction_t *tx = NULL;
	int i;

	full_len = len + llist_size(block->transactions) * SHA256_DIGEST_LENGTH;
	buf = calloc(1, full_len);
	if (!buf)
		return (NULL);
	start = buf;

	/* Copy the crucial infos */
	memcpy(buf, &block->info, len);
	buf += len; /* Len already embed the block->data.len too */

	for (i = 0; i < llist_size(block->transactions); i++)
	{
		tx = llist_get_node_at(block->transactions, i);
		memcpy(buf, tx->id, SHA256_DIGEST_LENGTH);
		buf += SHA256_DIGEST_LENGTH;
	}
	/* move pointer to start of buffer */
	buf = start;
	sha256(buf, full_len, hash_buf);
	free(start);
	return (hash_buf);
}
