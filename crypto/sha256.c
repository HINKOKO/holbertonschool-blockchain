#include "hblk_crypto.h"

/**
 * sha256 - computes the hash of a sequence of bytes
 * @s: sequence of bytes to be hashed
 * @len: number of bytes to hash in s
 * @digest: where to store the resulting hash
 * Return: pointer to digest, or NULL if digest happens to be NULL
 */

uint8_t *sha256(int8_t const *s, size_t len,
				uint8_t digest[SHA256_DIGEST_LENGTH])
{
	/* SHA256_Init, Update, and Final are the core functions */
	/* Allocate a context struct */
	SHA256_CTX ctx;
	/* Init that struct */
	SHA256_Init(&ctx);
	/* Run over the data with `Update` */
	SHA256_Update(&ctx, s, len);
	/* Extract the result with `Final` */
	SHA256_Final(digest, &ctx);
	if (!digest)
		return (NULL);

	return (digest);
}
