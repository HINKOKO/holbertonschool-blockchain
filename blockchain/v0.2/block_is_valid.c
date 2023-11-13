#include "blockchain.h"

#define CLEAR_HASH(h) (memset(h, 0, sizeof(h)))

/**
 * block_is_valid - Verifies that a Block is
 * => Not Invalid === Is valid hahaha!
 * @block: Pointer to the block to check
 * @prev_block: Pointer to previous Block
 * (NULL) if we stand on Genesis
 *
 * Return: EXIT_SUCCESS||FAILURE
 *
 * -> `block` shouldn't be NULL
 * -> prev_block can be NULL if only if block's index is 0
 * -> prev_block index must be current + 1
 * -> computed hash of prev_block must match the one it stores
 * -> computed hash of prev_block must match the one stored in 'block'
 * -> computed hash of 'block' must match the one it stores
 * -> block->data.len must not exceed BLOCKCHAIN_DATA_MAX
 * => we skip timestamp and difficulty for this iteration of the project
 */

int block_is_valid(block_t const *block, block_t const *prev_block)
{
	uint8_t hash_comparator[SHA256_DIGEST_LENGTH] = {0};
	block_t const gen_copy = GENESIS;

	if (!block || (!prev_block && block->info.index != 0))
		return (1);

	if (block->info.index == 0)
		return (memcmp(block, &gen_copy, sizeof(gen_copy)));

	if (block->info.index != prev_block->info.index + 1)
		return (1);
	if (!block_hash(prev_block, hash_comparator) ||
		memcmp(hash_comparator, prev_block->hash, SHA256_DIGEST_LENGTH) != 0)
		return (1);
	if (memcmp(prev_block->hash, block->info.prev_hash,
			   SHA256_DIGEST_LENGTH) != 0)
		return (1);
	CLEAR_HASH(hash_comparator);

	if (!block_hash(block, hash_comparator) ||
		memcmp(hash_comparator, block->hash, SHA256_DIGEST_LENGTH) != 0)
		return (1);
	/* Using our new match_difficulty functionality to extend validation */
	if (!hash_matches_difficulty(block->hash, block->info.difficulty))
		return (1);

	if (block->data.len > BLOCKCHAIN_DATA_MAX)
		return (1);
	return (0);
}
