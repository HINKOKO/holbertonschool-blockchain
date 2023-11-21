#include "transaction.h"

#define INPUTS 96
#define OUTPUTS 32

/**
 * transaction_hash - computes the ID (hash) of a transaction
 * @transaction: Points to the transaction to compute
 * @hash_buf: Buffer in which to store the computed hash
 * Return: Pointer to `hash_buf`
 * (transaction->id is left unchanged)
 * Transaction ID must be a hash of a buffer containing the following:
 * - Each input's (32 * 3 bytes)
 * - Each output's (32 bytes)
 *
 */

uint8_t *transaction_hash(transaction_t const *transaction,
						  uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{
	int i, offset = 0, all_inputs = 0, all_outputs = 0;
	int8_t *prehash = NULL;
	size_t prehash_len = 0;
	tx_in_t *temp_in = NULL;
	tx_out_t *temp_out = NULL;

	all_inputs = llist_size(transaction->inputs);
	all_outputs = llist_size(transaction->outputs);

	prehash_len = (all_inputs * INPUTS) + (all_outputs * OUTPUTS);
	prehash = malloc(prehash_len);
	if (!prehash || !transaction || !hash_buf)
		return (NULL);

	for (i = 0; i < all_inputs; i++)
	{
		temp_in = llist_get_node_at(transaction->inputs, i);
		memcpy(prehash + offset, temp_in, INPUTS);
		offset += INPUTS;
	}
	for (i = 0; i < all_outputs; i++)
	{
		temp_out = llist_get_node_at(transaction->outputs, i);
		memcpy(prehash + offset, temp_out, OUTPUTS);
		offset += OUTPUTS;
	}
	sha256(prehash, prehash_len, hash_buf);
	return (hash_buf);
}
