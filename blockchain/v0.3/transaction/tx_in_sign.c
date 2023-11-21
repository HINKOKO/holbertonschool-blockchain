#include "transaction.h"

/**
 * tx_in_sign - Signs a transaction input, given the transaction id it is from
 * @in: Points to the transaction input struct to sign
 * @tx_id: Contains the ID (hash) of the transaction input to sign
 * @sender: Contains the private key of the receveir of the coins
 * @all_unspent: List of all UTXOs
 * Return: Pointer to the resulting signature struct on success, NULL failure
 *
 * -> We verify the pub key derive from priv in `sender` match the pub stored
 * in tx output referenced by the tx input to be signed
 * -> We sign the ID of the tx `tx_id`
 */

sig_t *tx_in_sign(tx_in_t *in, uint8_t const tx_id[SHA256_DIGEST_LENGTH],
				  EC_KEY const *sender, llist_t *all_unspent)
{
	unspent_tx_out_t *find_it = NULL;
	uint8_t pub_checker[EC_PUB_LEN];
	size_t i, unspent_len = 0;

	if (!in || !tx_id || !sender ||
		!all_unspent || !ec_to_pub(sender, pub_checker))
		return (NULL);

	unspent_len = llist_size(all_unspent);
	for (i = 0; i < unspent_len; i++)
	{
		find_it = llist_get_node_at(all_unspent, i);
		if (!memcmp(in->tx_out_hash, find_it->out.hash, SHA256_DIGEST_LENGTH))
			break;
	}
	if (i == unspent_len)
		return (NULL);
	if (memcmp(pub_checker, find_it->out.pub, EC_PUB_LEN) ||
		!ec_sign(sender, tx_id, SIG_MAX_LEN, &in->sig))
		return (NULL);

	return (&in->sig);
}
