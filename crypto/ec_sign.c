#include "hblk_crypto.h"

#include <string.h>

/**
 * ec_sign - signs a given set of bytes, using EC_KEY privkey
 * @key: pointer to EC_KEY struct holding private key
 * @msg: points to msg_len character to be signed
 * @msglen: length of message to be signed
 * @sig: holds the aress at which to store signature
 * Return: On success -> a pointer to the signature buffer (sig->sig)
 * NULL on failure
 */

uint8_t *ec_sign(EC_KEY const *key, uint8_t const *msg, size_t msglen,
				 sig_t *sig)
{
	/* we don't know yet the sig len */
	unsigned int sig_len = 0;

	/* sanity checks */
	if (!key || !msg)
		return (NULL);

	if (ECDSA_sign(0, msg, msglen, sig->sig, &sig_len, (EC_KEY *)key) != 1)
		return (NULL);

	sig->len = (uint8_t)sig_len;

	return (sig->sig);
}
