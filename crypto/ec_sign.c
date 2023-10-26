#include "hblk_crypto.h"

#include <string.h>
#include <openssl/ecdsa.h>
#include <openssl/ec.h>
#include <openssl/evp.h>

void ECDSA_SIG_get0(const ECDSA_SIG *sig, const BIGNUM **pr, const BIGNUM **ps);

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
	ECDSA_SIG *ecdsa = NULL;
	const BIGNUM *r, *s;
	unsigned char *tmp_sig = NULL, *p = NULL;
	int sig_len = 0;

	ecdsa = ECDSA_do_sign(msg, msglen, (EC_KEY *)key);
	ECDSA_SIG_get0(ecdsa, &r, &s);

	sig_len = i2d_ECDSA_SIG(ecdsa, NULL);
	if (sig_len <= 0 || (size_t)sig_len > sizeof(sig->sig))
	{
		ECDSA_SIG_free(ecdsa);
		return (NULL);
	}
	tmp_sig = OPENSSL_malloc(sig_len);
	sig->len = (uint8_t)sig_len;

	p = tmp_sig;
	i2d_ECDSA_SIG(ecdsa, &p);

	memcpy(sig->sig, tmp_sig, sig->len);

	OPENSSL_free(tmp_sig);
	ECDSA_SIG_free(ecdsa);

	return (sig->sig);
}
