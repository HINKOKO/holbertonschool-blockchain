#include "transaction.h"

/**
 * coinbase_create - Creates a coinbase transaction
 * Let's give birth to some Coins !
 * @receiver: Public key of the brave miner who gets the coins
 * @block_index: Index of the Block the coinbase transaction will belongs to
 * Return: Pointer to created coinbase Transaction, NULL on failure
 * -- Resulting tx contains single input / single output
 * -- Transaction input zeroed, not signed. To ensure singularity, we copy
 * the block index in the 1st 4 bytes of input's `tx_out_hash`
 * -- Amount in tx output ==== COINBASE_AMOUNT macro
 */

transaction_t *coinbase_create(EC_KEY const *receiver, uint32_t block_index)
{
	transaction_t *tx_coin;
	tx_in_t *txin;
	tx_out_t *txo;
	uint8_t pub_miner[EC_PUB_LEN];

	tx_coin = calloc(1, sizeof(*tx_coin));
	if (!tx_coin)
		return (NULL);
	txin = calloc(1, sizeof(*txin));
	if (!txin || !receiver)
	{
		free(tx_coin);
		return (NULL);
	}

	memset(txin, 0, sizeof(*txin));
	memcpy(txin->tx_out_hash, &block_index, 4);

	ec_to_pub(receiver, pub_miner);
	txo = tx_out_create(COINBASE_AMOUNT, pub_miner);

	tx_coin->inputs = llist_create(MT_SUPPORT_FALSE);
	tx_coin->outputs = llist_create(MT_SUPPORT_FALSE);

	llist_add_node(tx_coin->inputs, txin, ADD_NODE_REAR);
	llist_add_node(tx_coin->outputs, txo, ADD_NODE_REAR);

	/* Finally hash the transaction */
	transaction_hash(tx_coin, tx_coin->id);
	return (tx_coin);
}
