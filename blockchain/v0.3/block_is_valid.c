#include "blockchain.h"

int check_tx(llist_node_t node, unsigned int idx, void *unspent)
{
	if (idx == 0)
		return (0);
	if (!transaction_is_valid(node, unspent))
		return (1);
	return (0);
}

/**
 * block_is_valid - Verifies that a Block is
 * => Not Invalid === Is valid hahaha!
 * @block: Pointer to the block to check
 * @prev_block: Pointer to previous Block
 * @all_unspent: Pointer to all utxos
 *
 * -- Updates --
 * A block must contain at least one transaction (at least coinbase tx)
 * The first transaction in a block must be a valid coinbase tx
 *
 * Return: EXIT_SUCCESS||FAILURE
 */

int block_is_valid(block_t const *block, block_t const *prev_block,
				   llist_t *all_unspent)
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
		memcmp(hash_comparator, prev_block->hash, SHA256_DIGEST_LENGTH) ||
		memcmp(prev_block->hash, block->info.prev_hash, SHA256_DIGEST_LENGTH) ||
		!block_hash(block, hash_comparator))

		if (!block_hash(block, hash_comparator) ||
			memcmp(hash_comparator, block->hash, SHA256_DIGEST_LENGTH) != 0)
			return (1);
	/* Using our new match_difficulty functionality to extend validation */
	if (!hash_matches_difficulty(block->hash, block->info.difficulty))
		return (1);

	if (block->data.len > BLOCKCHAIN_DATA_MAX)
		return (1);
	/* Updated additional checks */
	if (llist_size(block->transactions) < 1)
		return (1);
	if (!coinbase_is_valid(llist_get_head(block->transactions),
						   block->info.index))
		return (1);

	return (0);
	(void)all_unspent; /* DIsabled for the moment */
}
