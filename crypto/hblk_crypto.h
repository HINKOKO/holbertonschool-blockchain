#ifndef __HBTN_CRYPTO__
#define __HBTN_CRYPTO__

#include <stdint.h>
#include <string.h>
/* stdint types will maintain size regardless architecture */
#include <openssl/sha.h>
/* For the EC materials */
#include <openssl/ec.h>
#include <openssl/obj_mac.h>
#include <openssl/ecdsa.h>

/* Bitcoin curve y^2 = x^3 + 7 */
#define EC_CURVE NID_secp256k1

/* EC_KEY public key octet string length (using 256-bit curve) */
#define EC_PUB_LEN 65
/* Maximum signature octet string length (using 256-bit curve) */
#define SIG_MAX_LEN 72

#define PRI_FILENAME "key.pem"
#define PUB_FILENAME "key_pub.pem"

/**
 * struct sig_s - EC Signature structure
 * @sig: Signature buffer. The whole spae may not be used
 * => sig must stay first, so we can directly use the
 * structure as an array of char
 * @len: Actual signature size. Can't exceed SIG_MAX_LEN, therefore stored
 * on a byte
 */

typedef struct sig_s
{
	uint8_t sig[SIG_MAX_LEN];
	uint8_t len;
} sig_t;

/* Protozo-aires */
uint8_t *sha256(int8_t const *s, size_t len,
				uint8_t digest[SHA256_DIGEST_LENGTH]);
EC_KEY *ec_create(void);
uint8_t *ec_to_pub(EC_KEY const *key, uint8_t pub[EC_PUB_LEN]);
EC_KEY *ec_from_pub(uint8_t const pub[EC_PUB_LEN]);
int ec_save(EC_KEY *key, char const *folder);
EC_KEY *ec_load(char const *folder);
uint8_t *ec_sign(EC_KEY const *key, uint8_t const *msg,
				 size_t msglen, sig_t *sig);

#endif /* __HBTN_CRYPTO__ */
