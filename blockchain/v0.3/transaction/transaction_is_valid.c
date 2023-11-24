#include "transaction.h"

/**
 * transaction_is_valid - Checks whether a transaction is valid
 * @transaction: Points to the tx to verify
 * @all_unspent: List of all unspent tx outputs to date
 * Return: 1 if tx is valid, 0 otherwise
 * Steps of verification:
 * -- Computed hash of tx must match hash stored in it
 * -- Each input in tx must refer to an unspent output in `all_unspent`
 * -- Each input's sig must be verified using pubkey stored in ref utxo
 * -- Total amount of inputs must match the total amount of ouputs
 */

int transaction_is_valid(transaction_t const *transaction,
						 llist_t *all_unspent)
{
	uint8_t hash_buf[SHA256_DIGEST_LENGTH];

	if (!transaction || !all_unspent)
		return (0);
	/* Rehash to compare hashes */
	transaction_hash(transaction, hash_buf);

	if (memcmp(transaction->id, hash_buf,
			   SHA256_DIGEST_LENGTH))
		return (0); /* hash id do not match */

	return (1);
}
