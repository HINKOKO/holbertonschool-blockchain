#include "transaction.h"

#include <unistd.h>

/**
 * sign_transaction - Sign tx inputs using tx->id passed in args
 * @node: Node of LL of tx inputes
 * @idx: index -> Unused
 * @args: array of arguments
 * Return: 0 Success, 1 if Failure
 */

int sign_transaction(llist_node_t node, unsigned int idx, void *args)
{
	tx_in_t *tx_in = node;
	void **ptr = args;

	if (!tx_in_sign(tx_in, ptr[0], ptr[1], ptr[2]))
		return (1);
	return (0);
	(void)idx;
}

/**
 * send_money - Send coins to receiver 'r', and eventually
 * create a new utxo's for the leftover to the sender 's'
 * @s: EC_KEY pair of sender
 * @r: EC_KEY pair of receiver
 * @amount: Amount being sent
 * @total_money: Available money of the sender
 * Return: Pointer to the txo which embed the leftover for the sender
 * or NULL on failure
 */

llist_t *send_money(EC_KEY const *s, EC_KEY const *r,
					uint32_t amount, uint32_t total_money)
{
	tx_out_t *tx_out;
	llist_t *out; /* 'Shared' list of tx_out */
	uint32_t leftover = total_money - amount;
	uint8_t pub[EC_PUB_LEN];

	out = llist_create(MT_SUPPORT_FALSE);
	ec_to_pub(r, pub);
	tx_out = tx_out_create(amount, pub);
	llist_add_node(out, tx_out, ADD_NODE_REAR);
	if (leftover)
	{
		ec_to_pub(s, pub);
		tx_out = tx_out_create(leftover, pub);
		llist_add_node(out, tx_out, ADD_NODE_REAR);
	}
	return (out);
}

/**
 * collect_unspent - The actual 'action' being performerd on each node
 * of the all_unspent list -> Collect valids UTXO's of the sender
 * @node: Custom node from opaque llist_node_t struct, here
 * we are 'casting' it to an `unspent_tx_out` "node" (what we need actually)
 * @idx: Index which iterates on the `llist_for_each` invocation (unused)
 * @args: Pointer to arguments which were passed to the `llist_for_each`
 * -> To pass additional info to this function, very neat.
 * Return: Always SUCCESS
 */

int collect_unspent(llist_node_t node, unsigned int idx, void *args)
{
	unspent_tx_out_t *browser = node;
	/* args interpreted as pointer to an array of void pointers */
	/* Common tech in C to pass mult pieces of data through single pointer */
	void **ptr = args;
	llist_t *inputs = ptr[1];
	uint32_t *money = ptr[2];
	tx_in_t *tx_in; /* What we want to create as we collect */

	if (!memcmp(browser->out.pub, ptr[0], EC_PUB_LEN))
	{
		tx_in = tx_in_create(browser);
		llist_add_node(inputs, tx_in, ADD_NODE_REAR);
		*money += browser->out.amount;
	}
	return (EXIT_SUCCESS);
	(void)idx;
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
 * pub_key match `sender` privatekey => `collect_unspent()`
 * -- Create tx inputs from these selected UTXO's => `collect_unspent()`
 * -- Function must FAILS if sender doesn't possess enough coins
 * (UTXO's < amount) => Checked in `transaction_create()`
 * -- Create a tx output, sending `amount` coins to `receiver's` pubkey
 * -- If total UTXO's amount > amount => Create 2nd tx output,
 * for sending leftover back to `sender` => Performed in `send_money()`
 * -- Compute tx ID (hash)
 * -- Sign tx inputs using previously computed tx ID => We hash ID of tx in
 * `transaction_create`, iterate on txinputs to sign 'em in `sign_transaction`
 */

transaction_t *transaction_create(EC_KEY const *sender, EC_KEY const *receiver,
								  uint32_t amount, llist_t *all_unspent)
{
	transaction_t *tx;
	uint8_t pub[EC_PUB_LEN]; /* 'Buffer' to extract pub keys of both parties */
	void *args[3] = {0};	 /* Array to hold 3 void pointers */
	llist_t *tx_out, *tx_in = llist_create(MT_SUPPORT_FALSE);
	uint32_t total_money = 0;

	tx = calloc(1, sizeof(*tx));
	if (!tx || !sender || !receiver || !amount || !all_unspent)
		return (NULL);
	if (!ec_to_pub(sender, pub))
		return (fprintf(stderr, "Error: Failed to extract sender pub key"),
				NULL);
	/* Pick the args we"re gonna need for this operation of collect */
	args[0] = pub, args[1] = tx_in, args[2] = &total_money;
	llist_for_each(all_unspent, collect_unspent, args);

	if (total_money < amount)
	{
		free(tx);
		return (NULL);
	}
	tx_out = send_money(sender, receiver, amount, total_money);
	tx->inputs = tx_in, tx->outputs = tx_out;
	transaction_hash(tx, tx->id);
	/* Assign new arguments for signing */
	args[0] = tx->id, args[1] = (void *)sender, args[2] = all_unspent;
	llist_for_each(tx->inputs, sign_transaction, args);
	return (tx);
}
