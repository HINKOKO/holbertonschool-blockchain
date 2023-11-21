#include "transaction.h"

/**
 * unspent_tx_out - Alloc and Init an UTXO struct
 * @block_hash: The hash of the Block where referenced tx is located
 * @tx_id: The hash of a tx in the Block `block_hash`, where ref tx is located
 * @out: Points to the referenced transaction output
 * Return: Pointer to the created unspent transaction output upon success
 * NULL on failure
 */

unspent_tx_out_t *unspent_tx_out_create(uint8_t
											block_hash[SHA256_DIGEST_LENGTH],
										uint8_t tx_id[SHA256_DIGEST_LENGTH], tx_out_t const *out)
{
	unspent_tx_out_t *utxo = calloc(1, sizeof(*utxo));

	if (!utxo || !block_hash || !tx_id || !out)
		return (NULL);

	memcpy(utxo->block_hash, block_hash, SHA256_DIGEST_LENGTH);
	memcpy(utxo->tx_id, tx_id, SHA256_DIGEST_LENGTH);
	memcpy(&(utxo->out), out, sizeof(utxo->out));
	return (utxo);
}
