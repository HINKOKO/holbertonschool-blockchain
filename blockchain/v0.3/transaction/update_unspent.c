#include "transaction.h"

/**
 * unspent_match - Utility function to compare unspent_tx_out
 * from all unspent to the tx passed as inputs
 * @utxo: Pointer to unspent tx_out_t
 * @tx_in: Pointer to transaction input 'node'
 * Return: 1 for 'success' match, 0 otherwise
 */

int unspent_match(unspent_tx_out_t *utxo, tx_in_t *tx_in)
{
	if (memcmp(utxo->out.hash, tx_in->tx_out_hash, SHA256_DIGEST_LENGTH) ||
		memcmp(utxo->tx_id, tx_in->tx_id, SHA256_DIGEST_LENGTH))
		return (0);
	return (1);
}

/**
 * update_unspent - Updates the list of all_unspent tx, given a list of
 * processed transactions
 * @transactions: List of validated transactions
 * @block_hash: Hash of the validated block
 * (that contains the transaction list `transactions`)
 * @all_unspent: Current list of unspent tx outputs
 * Return: (create) && return a pointer to a new list of utxos
 * -- All tx inputs shouldn't be included in new returned list
 * -- All tx outputs should be appended in new returned list
 * -- List all_unspent deleted upon Success
 */

llist_t *update_unspent(llist_t *transactions,
						uint8_t block_hash[SHA256_DIGEST_LENGTH], llist_t *all_unspent)
{
	llist_t *new_utxo = llist_create(MT_SUPPORT_FALSE);
	int i, j, k, tx_size = llist_size(transactions);
	transaction_t *tx;
	tx_in_t *in_node;
	tx_out_t *out_node;
	unspent_tx_out_t *utxo;

	for (i = 0; i < llist_size(all_unspent); i++)
	{
		utxo = llist_get_node_at(all_unspent, i);
		for (j = 0; j < tx_size; j++)
		{
			tx = llist_get_node_at(transactions, j);
			for (k = 0; k < llist_size(tx->inputs); k++)
			{
				in_node = llist_get_node_at(tx->inputs, j);
				if (unspent_match(utxo, in_node))
					break;
			}
			if (k < llist_size(tx->inputs))
				break;
		}
		if (j == tx_size)
			llist_add_node(new_utxo, utxo, ADD_NODE_REAR);
		else
			free(utxo);
	}
	/* Loop through all transaction->outputs that we all append */
	for (i = 0; i < tx_size; i++)
	{
		tx = llist_get_node_at(transactions, i);
		for (j = 0; j < llist_size(tx->outputs); j++)
		{
			out_node = llist_get_node_at(tx->outputs, j);
			utxo = unspent_tx_out_create(block_hash, tx->id, out_node);
			llist_add_node(new_utxo, utxo, ADD_NODE_REAR);
		}
	}
	llist_destroy(all_unspent, 0, NULL);
	return (new_utxo);
}
