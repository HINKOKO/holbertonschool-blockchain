#include "blockchain.h"

/**
 * check_unspent - Iterates through utxos
 * and check their validity
 * @block: Pointer to block to verify
 * @unspent: Pointer to list of unspent tx
 * Return: 1 if ok, 0 otherwise
 */

int check_unspent(block_t const *block, llist_t *unspent)
{
	int i;
	transaction_t *node;

	for (i = 0; i < llist_size(block->transactions); i++)
	{
		node = llist_get_node_at(block->transactions, i);
		if (i == 0 && !coinbase_is_valid(node, block->info.index))
			return (-1);
		if (i > 0 && !transaction_is_valid(node, unspent))
			return (-1);
	}
	/* 'i' stucked at 0 means no transactions in block -> Bad */
	if (i == 0)
		return (-1);
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
		memcmp(hash_comparator, prev_block->hash, SHA256_DIGEST_LENGTH))
		return (1);
	if (memcmp(prev_block->hash, block->info.prev_hash, SHA256_DIGEST_LENGTH))
		return (1);

	if (!block_hash(block, hash_comparator) ||
		memcmp(hash_comparator, block->hash, SHA256_DIGEST_LENGTH) != 0)
		return (1);

	if (!hash_matches_difficulty(block->hash, block->info.difficulty))
		return (1);

	if (block->data.len > BLOCKCHAIN_DATA_MAX)
		return (1);

	/* Updated additional checks */
	if (check_unspent(block, all_unspent) == -1)
		return (1);

	return (0);
}
