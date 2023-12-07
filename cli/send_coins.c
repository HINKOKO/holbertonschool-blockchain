#include "cli.h"
#include <ctype.h>

/*int pack_key(char *arg, uint8_t pub[EC_PUB_LEN])
{
	uint32_t i = 0, j = 0, left, right;

	if (strlen(arg) != 130)
		return (0);

	while (i < EC_PUB_LEN)
	{
		left = arg[j];
		if (left >= 97)
			left -= 87;
		else
			left -= 48;
		right = arg[j + 1];
		if (right >= 97)
			right -= 87;
		else
			right -= 48;

		if (left > 15 || right > 15)
			return (0);

		pub[i] = left << 4;
		pub[i] += right;
		j += 2;
		i += 1;
	}
	return (1);
} */

int pack_key(char *arg, uint8_t pub[EC_PUB_LEN])
{
	size_t i, len_key = strlen(arg);

	if (len_key != 130)
	{
		fprintf(stderr, "Wrong key length :// \n");
		return (0);
	}
	for (i = 0; i < EC_PUB_LEN; i++)
	{
		if (sscanf(&arg[i * 2], "%2x", (unsigned int *)&pub[i]) < 1)
		{
			fprintf(stderr, "packing failed\n");
			return (0);
		}
	}
	return (1);
}

/**
 * cmd_send_coins - Send coins
 * -- Create a new transaction
 * -- Verify the transaciton validity
 * -- Add transaction to local list (transaction pool)
 * -- Do not update list of unspent
 *
 */

int cmd_send_coins(bc_t **bc, block_t **active, EC_KEY **key, char *arg1, char *arg2)
{
	uint32_t amount;
	EC_KEY *receiver;
	local_tx_t *tx_pool = NULL;
	transaction_t *tx;
	uint8_t pub[EC_PUB_LEN] = {0};

	if (!arg1 || !arg2)
	{
		fprintf(stderr, "Usage: send <amount> <address>\n");
		return (0);
	}

	/* Cooking arguments */
	amount = atoi(arg1);
	if (!amount)
		return (fprintf(stderr, "Amount should be greater than 0\n"), 0);

	/* Handle the key -> back to a pub buffer */
	if (!pack_key(arg2, pub))
		return (fprintf(stderr, "Problem with recipient key\n"), 0);

	receiver = ec_from_pub(pub);
	if (!receiver)
		return (fprintf(stderr, "Cannot handle your public key recipient\n"), 0);
	/* Create transaction */
	tx = transaction_create(*key, receiver, (uint32_t)amount, (*bc)->unspent);
	if (!tx)
	{
		EC_KEY_free(receiver);
		return (fprintf(stderr, "Transaction failed\n"), 0);
	}
	tx_pool->tx_pool = llist_create(MT_SUPPORT_FALSE);
	llist_add_node(tx_pool->tx_pool, tx, ADD_NODE_REAR);
	/* llist_add_node((*active)->transactions, tx, ADD_NODE_REAR); */
	EC_KEY_free(receiver);
	printf("Transaction completed successfully\n");
	return (1);
	(void)active;
}
