#include "hblk_crypto.h"

#define FAILHAPPENED 33

/**
 * ec_verify - verifies the signature of a given set of bytes
 * using a provided EC_KEY pub key
 * @key: points to EC_KEY struct containing pub_key
 * @msg: points to msglen characters to verify the signature
 * @msglen: len of the signed message
 * @sig: points to the signature to be checked
 * Return: must fail on failure, 1 for successful check
 */

int ec_verify(EC_KEY const *key, uint8_t const *msg, size_t msglen,
			  sig_t const *sig)
{
	if (ECDSA_verify(0, msg, msglen, sig->sig, sig->len, (EC_KEY *)key) != 1)
		return (FAILHAPPENED);

	return (1);
}
