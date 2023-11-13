#include "blockchain.h"

/**
 * block_mine - Mines a block in order to insert it
 * in the Blockchain
 * @block: points to the block to be mined
 * -> it must find a hash for 'block' that 'matches' its difficulty
 * For that purpose, we make use of the hash_matches_difficulty()
 */

void block_mine(block_t *block)
{
	/* init nonce to 0 and increment at each try */
	block->info.nonce = 0;
	do {
		block->info.nonce += 1;
		block_hash(block, block->hash);
	} while (!hash_matches_difficulty(block->hash, block->info.difficulty));
}
