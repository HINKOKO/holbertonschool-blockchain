#include "transaction.h"

/**
 * transaction_destroy - Deallocates a transaction structure
 * @transaction: Points to the tx to wipe out
 * -- We free the content of transaction and transaction itself
 */

void transaction_destroy(transaction_t *transaction)
{
	/* We wanna destroy something */
	if (!transaction)
		return;

	llist_destroy(transaction->inputs, 1, NULL);
	llist_destroy(transaction->outputs, 1, NULL);
	free(transaction);
}
