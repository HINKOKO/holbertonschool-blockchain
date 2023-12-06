#include "cli.h"

#define EC_COMP 33

void ec_compressed(EC_KEY *key, uint8_t pub[EC_COMP])
{
	size_t pubkey_len = 0, i;
	const EC_GROUP *grp = NULL;
	const EC_POINT *pkey = NULL;

	if (!key || !pub)
		return;

	grp = EC_KEY_get0_group(key);
	pkey = EC_KEY_get0_public_key(key);
	if (!grp || !pkey)
		return;

	EC_KEY_set_conv_form((EC_KEY *)key, POINT_CONVERSION_COMPRESSED);
	pubkey_len = EC_POINT_point2oct(grp, pkey, POINT_CONVERSION_COMPRESSED, NULL, 0, NULL);
	if (pubkey_len != EC_COMP)
		return;

	EC_POINT_point2oct(grp, pkey, POINT_CONVERSION_COMPRESSED, pub, pubkey_len, NULL);
	for (i = 0; i < EC_COMP; i++)
		printf("%02x", pub[i]);
	printf("\n");
}

/**
 * cmd_wallet_load - Loads a wallet from a path
 *
 */

int cmd_wallet_load(bc_t **bc, block_t **active, EC_KEY **key, char *arg1, char *arg2)
{
	EC_KEY *out;
	uint8_t pub[EC_COMP];

	if (arg1 == NULL)
	{
		fprintf(stderr, "Usage: wallet_load <path>\n");
		return (0);
	}

	out = ec_load(arg1);
	if (!out)
		return (fprintf(stderr, "Failed to load from folder %s\n", arg1), 0);
	*key = out;
	printf("Wallet loaded successfully \n");
	ec_compressed(*key, pub);
	return (1);
	(void)bc;
	(void)active;
	(void)arg2;
}
