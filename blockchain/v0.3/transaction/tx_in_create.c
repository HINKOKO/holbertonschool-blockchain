#include "transaction.h"

/**
 * tx_in_create - Alloc & Init a tx_in_struct
 * @unspent: Points to the unspent tx output to be converted
 * to a tx input
 * Return: Pointer to the created tx input on success,
 * NULL on failure
 * -> Created transaction input's signature must be zeroe'd
 */

tx_in_t *tx_in_create(unspent_tx_out_t const *unspent)
{
	tx_in_t *inp = calloc(1, sizeof(*inp));

	if (!inp || !unspent)
		return (NULL);

	memcpy(inp->block_hash, unspent->block_hash, SHA256_DIGEST_LENGTH);
	memcpy(inp->tx_id, unspent->tx_id, SHA256_DIGEST_LENGTH);
	memcpy(inp->tx_out_hash, unspent->out.hash, SHA256_DIGEST_LENGTH);
	memset(&(inp->sig), 0, 0);

	return (inp);
}
