#include "transaction.h"

#include <unistd.h>

// if (!sign_input(tx, sender, all_unspent))

int sign_input(transaction_t *tx, EC_KEY const *sender, llist_t *all_unspent)
{
	tx_in_t *txi;
	uint32_t i = 0, len = llist_size(tx->inputs);

	if (!transaction_hash(tx, tx->id))
		return (0);
	for (i = 0; i < len; i++)
	{
		txi = llist_get_node_at(tx->inputs, i);
		if (!tx_in_sign(txi, txi->tx_id, sender, all_unspent))
			return (0);
	}
	return (1);
}

transaction_t *create_utxos(uint32_t amount, uint8_t pub_s[EC_PUB_LEN],
							uint8_t pub_r[EC_PUB_LEN], transaction_t *tx, uint32_t unspent)
{
	tx_out_t *txo_receiver = NULL, *txo_sender = NULL;

	if (unspent > amount)
	{
		txo_sender = tx_out_create(unspent - amount, pub_s);
	}
	txo_receiver = tx_out_create(amount, pub_r);

	if (llist_add_node(tx->outputs, txo_receiver, ADD_NODE_REAR) ||
		(txo_sender && llist_add_node(tx->inputs, txo_sender, ADD_NODE_REAR)))
		return (NULL);

	return (tx);
}

int populate_input(llist_t *valids, uint32_t amount, uint8_t pub[EC_PUB_LEN], transaction_t *tx)
{
	unspent_tx_out_t *nodes = calloc(1, sizeof(*nodes));
	int i, len = llist_size(valids);
	tx_in_t *txi = NULL;

	for (i = 0; i < len; i++)
	{
		nodes = llist_pop(valids);
		txi = tx_in_create(nodes);
		if (!txi)
			return (0);
		if (llist_add_node(tx->inputs, txi, ADD_NODE_REAR))
			return (0);
	}
	return (1);
	(void)amount;
}

/**
 * collect_unspent - Collect from UTXO's the
 * @all_unspent: list of UTXOs
 * @pub_sender: contains pub key of sender
 * Return: uint32_t amount of available money from UTXOs the senser posess
 */

uint32_t collect_valid_utxo(llist_t *all_unspent, uint8_t pub_sender[EC_PUB_LEN], llist_t *valids)
{
	unspent_tx_out_t *browser = NULL;
	int i, unspent_len = llist_size(all_unspent);
	uint32_t money = 0;

	for (i = 0; i < unspent_len; i++)
	{
		browser = llist_get_node_at(all_unspent, i);
		if (memcmp(browser->out.pub, pub_sender, EC_PUB_LEN) == 0)
		{
			money += browser->out.amount;
			llist_add_node(valids, browser, ADD_NODE_REAR);
		}
	}

	return (money);
}

/**
 * transaction_create - Creates a transaction
 * @sender: Private key of transaction sender
 * @receiver: Public key of transaction receiver
 * @amount: Amount to be sent
 * @all_unspent: List of all unspent output to date
 *
 * Return: Pointer to the created transaction, NULL on failure
 * Steps ==>
 * -- Select a set of unspent tx outputs from `all_unspent`, which
 * pub_key match `sender` privatekey
 * -- Create tx inputs from these selected UTXO's
 * -- Function must FAILS if sender doesn't possess enough coins
 * (UTXO's < amount)
 * -- Create a tx output, sending `amount` coins to `receiver's` pubkey
 * -- If total UTXO's amount > amount => Create 2nd tx output,
 * for sending leftover back to `sender`
 * -- Compute tx ID (hash)
 * -- Sign tx inputs using previously computed tx ID
 */

transaction_t *transaction_create(EC_KEY const *sender, EC_KEY const *receiver,
								  uint32_t amount, llist_t *all_unspent)
{
	transaction_t *tx;
	llist_t *valids = llist_create(MT_SUPPORT_TRUE);
	uint8_t pub_sender[EC_PUB_LEN], pub_receiver[EC_PUB_LEN];
	uint32_t sender_money = 0;

	/* Check that everythin is provided for tx */
	if (!sender || !receiver || !amount || !all_unspent)
		return (NULL);
	if (!ec_to_pub(sender, pub_sender) || !ec_to_pub(receiver, pub_receiver))
		return (fprintf(stderr, "Failed to read sender pub key"), NULL);

	/* Collect UTXOs that matches and computes money available */
	sender_money = collect_valid_utxo(all_unspent, pub_sender, valids);
	if (sender_money < amount)
		return (fprintf(stderr, "Not enough money, get back to work"), NULL);

	tx = calloc(1, sizeof(*tx));
	tx->inputs = llist_create(MT_SUPPORT_FALSE);
	tx->outputs = llist_create(MT_SUPPORT_FALSE);

	if (!populate_input(valids, amount, pub_sender, tx))
		return (NULL);

	tx = create_utxos(amount, pub_sender, pub_receiver, tx, sender_money);
	if (!tx)
		return (NULL);

	if (!sign_input(tx, sender, all_unspent))
		return (free(tx), NULL);

	return (tx);
}
