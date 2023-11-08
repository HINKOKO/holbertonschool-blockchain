#include "blockchain.h"

/**
 * block_hash - computes the hash of a Block
 * --> we take the sha256 in our crypto/ previous project
 * @block: points to the block to be hashed
 * @hash_buf: where to store resulting hash
 *
 * Return: a pointer to hash_buf -> Using the 'sha256()' function
 * from folder 'crypto', function which returns pointer to hash_buf already
 */

uint8_t *block_hash(block_t const *block,
					uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{
	/* When hashing a block, we hash info + data */
	size_t len = 0;

	len = sizeof(block->info) + block->data.len;

	return (sha256((int8_t const *)block, len, hash_buf));
}
