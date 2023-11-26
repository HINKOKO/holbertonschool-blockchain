#include "transaction.h"

/**
 * check_input_zeroed - Checks whether input"s fields
 * are effectively zeroed
 * @inputs: the tx input to be checked
 * Return: 1 if evrything okay, 0 if any field is not cleared
 */

int check_input_zeroed(tx_in_t *inputs)
{
	tx_in_t zero;

	memset(&zero, 0, sizeof(zero));
	if (memcmp(inputs->block_hash, zero.block_hash, SHA256_DIGEST_LENGTH))
		return (0);
	if (memcmp(inputs->tx_id, zero.tx_id, SHA256_DIGEST_LENGTH))
		return (0);
	if (inputs->sig.len != 0)
		return (0);

	return (1);
}

/**
 * coinbase_is_valid - Checks wheter a coinbase tx is valid
 * @coinbase: Points to the coinbase tx to check
 * @block_index: Index of the Block the coinbase will belong to
 * Return: 1 if valid, 0 otherwise
 * -- Computed hash of tx must match hash stored in it
 * -- Tx must contain EXACTLY 1 input
 * -- Tx must contain EXAXCTLY 1 output
 * -- Tx input's `tx_out_hash` first 4 bytes must match `block_index`
 * -- Tx input's `block_hash`, `tx_id` must me ZEROED
 * -- Tx output amount must be exactly COINBASE_AMOUNT
 */

int coinbase_is_valid(transaction_t const *coinbase, uint32_t block_index)
{
	uint8_t hash_buf[SHA256_DIGEST_LENGTH]; /* testing buff */
	tx_in_t *txin = NULL;
	tx_out_t *txo = NULL;

	transaction_hash(coinbase, hash_buf);
	if (memcmp(coinbase->id, hash_buf, SHA256_DIGEST_LENGTH))
		return (0); /* Mismatch of hashes*/

	if (llist_size(coinbase->inputs) != 1 ||
		llist_size(coinbase->outputs) != 1)
		return (0);

	txin = llist_get_head(coinbase->inputs);
	if (memcmp(txin->tx_out_hash, &block_index, 4))
		return (0);
	if (!check_input_zeroed(txin))
		return (0);

	txo = llist_get_head(coinbase->outputs);
	if (txo->amount != COINBASE_AMOUNT)
		return (0);

	return (1);
}
