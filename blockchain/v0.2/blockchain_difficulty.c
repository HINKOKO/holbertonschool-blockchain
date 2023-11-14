#include "blockchain.h"

/**
 * blockchain_difficulty - computes the difficulty to assign
 * a potential next Block in the Blockchain
 * @blockchain: pointer to the Bchain to analyze
 * Return: The diffuculty to be assigned to a potential Block
 */

uint32_t blockchain_difficulty(blockchain_t const *blockchain)
{
	uint64_t elapsed = 0, expected = 0;
	block_t *last = NULL, *last_adjusted = NULL;

	last = llist_get_tail(blockchain->chain);

	if (!last || last->info.index == 0 ||
		last->info.index % DIFFICULTY_ADJUSTMENT_INTERVAL != 0)
		return (last->info.difficulty);
	/* at 'first' last adjusted is the last too */
	/* when % DIFFCULTY => returns 0, the index is forcefully set to 5 */
	/* add +1 to it avoid jumping back to 0 in the get_node_at(..idx 0) */
	last_adjusted = llist_get_node_at(blockchain->chain,
									  (last->info.index + 1 - DIFFICULTY_ADJUSTMENT_INTERVAL));

	elapsed = last->info.timestamp - last_adjusted->info.timestamp;
	expected = BLOCK_GENERATION_INTERVAL * DIFFICULTY_ADJUSTMENT_INTERVAL;

	if (elapsed < (expected / 2))
		return (last->info.difficulty + 1);
	else if (elapsed > (expected * 2))
		return (last->info.difficulty - 1);
	else
		return (last->info.difficulty);
}
