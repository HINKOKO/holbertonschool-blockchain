#include "hblk_crypto.h"

/**
 * ec_from_pub - creates an EC_KEY struct given a pub key
 * @pub: holds the pub key to be converted
 * Return: pointer to EC_KEY struct || NULL on failure
 */

EC_KEY *ec_from_pub(uint8_t const pub[EC_PUB_LEN])
{
	const EC_GROUP *group = NULL;
	EC_POINT *public_key = NULL;
	EC_KEY *new_ec = EC_KEY_new_by_curve_name(EC_CURVE);

	if (!new_ec)
		return (NULL);

	/* Creates an EC_POINT from the pub key bytes */
	group = EC_KEY_get0_group(new_ec);
	public_key = EC_POINT_new(group);

	if (!public_key)
	{
		EC_KEY_free(new_ec);
		return (NULL);
	}

	if (EC_POINT_oct2point(group, public_key, pub, EC_PUB_LEN, NULL) == 0)
	{
		EC_POINT_free(public_key);
		EC_KEY_free(new_ec);
		return (NULL);
	}
	/* set the public key to the struct */
	if (EC_KEY_set_public_key(new_ec, public_key) == 0)
	{
		EC_POINT_free(public_key);
		EC_KEY_free(new_ec);
		return (NULL);
	}
	EC_POINT_free(public_key);
	return (new_ec);
}
