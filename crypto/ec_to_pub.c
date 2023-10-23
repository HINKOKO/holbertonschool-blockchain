#include "hblk_crypto.h"

/**
 * ec_to_pub - extracts the public key from
 * the opaque EC_KEY blackbox
 * @key: pointer to EC_KEY struct, if NULL
 * => we return and do nothing at all
 * @pub: address at which to store the extracted pub key
 * => shall not be compressed
 * Return: Must return a pointer to pub
 * NULL must be returned on FAILURE
 */

uint8_t *ec_to_pub(EC_KEY const *key, uint8_t pub[EC_PUB_LEN])
{
	size_t pub_key_len = 0;
	const EC_GROUP *group = NULL;
	const EC_POINT *pkey_point = NULL;
	EC_POINT *pubkey = NULL;
	/* Actually the EC_KEY_get0_public_key return ? check proto*/
	/* get the EC_POINT public key, we need an EC_POINT */
	/* const EC_POINT *EC_KEY_get...(const EC_KEY *key)*/

	/* sanity checks */
	if (!key || !pub)
		return (NULL);

	group = EC_KEY_get0_group(key);
	/* EC_KEY_get0_public_key returns EC_POINT */
	pkey_point = EC_KEY_get0_public_key(key);

	if (!group || !pkey_point)
		return (NULL);

	/* copy for not modifying original ? */
	pubkey = EC_POINT_new(group);
	if (!EC_POINT_copy(pubkey, pkey_point))
	{
		EC_POINT_free(pubkey);
		return (NULL);
	}
	/* EC_POINT_point2oct => returns size_t // encodes */
	/* given curve point as octect string */
	pub_key_len = EC_POINT_point2oct(group, pubkey, 4, NULL, 0, NULL);
	if (pub_key_len > EC_PUB_LEN)
	{
		EC_POINT_free(pubkey);
		return (NULL);
	}
	EC_POINT_point2oct(group, pubkey, 4, pub, pub_key_len, NULL);
	EC_POINT_free(pubkey);

	return (pub);
}
