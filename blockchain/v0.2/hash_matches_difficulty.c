#include "blockchain.h"

/**
 * hash_matches_difficulty - checks whether a given hash matches
 * a given difficulty
 * @hash: hash to check
 * @difficulty: the minimum difficulty the hash shoud match
 * Return: 1 if difficulty respected, 0 otherwise
 */

int hash_matches_difficulty(uint8_t const hash[SHA256_DIGEST_LENGTH],
							uint32_t difficulty)
{
	uint32_t i;

	if (!hash || difficulty <= 0)
		return (0);
	for (i = 0; i < difficulty / 8; i++)
		if (hash[i] != 0)
			return (0); /* Hash does not has required numbers of zeros */
	/* if difficulty not multiple of 8 bits */
	if (difficulty % 8 != 0 && (hash[difficulty / 8] >> (8 - difficulty % 8)) != 0)
		return (0);

	return (1);
}
