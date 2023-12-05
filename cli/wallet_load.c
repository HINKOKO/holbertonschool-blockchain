#include "cli.h"

#define CMD "\033[31m"
#define RESET "\033[0m"

uint8_t *ec_to_pub_compress(EC_KEY const *key, uint8_t pub[EC_COMP])
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

void display_compressed(EC_KEY *key)
{
	uint8_t buff[EC_COMP];
	const EC_GROUP *grp = EC_KEY_get0_group(key);
	EC_KEY *comp = EC_KEY_new();

	if (!EC_KEY_set_group(comp, grp))
	{
		fprintf(stderr, "Failed to set group for compressed key\n");
		EC_KEY_free(comp);
		return;
	}
	EC_KEY_set_conv_form(comp, POINT_CONVERSION_COMPRESSED);
	ec_to_pub_compress(comp, buff);
	_print_hex_buffer(buff, EC_COMP);
	printf("\n");
}

/**
 * cmd_wallet_load - Loads a wallet from a path
 *
 */

int cmd_wallet_load(bc_t **bc, block_t **active, EC_KEY **key, char *arg1, char *arg2)
{
	int choice;
	EC_KEY *out;

	if (arg1 == NULL)
	{
		printf("Usage: wallet_load <path>\n");
		printf("%sNote that the CLI loaded by default a key-pair%s\n", CMD, RESET);
		printf("\tPress %s1%s for using default\n\tPress %s2%s to go back to home\n", CMD, RESET, CMD, RESET);
		if (scanf("%d", &choice) != 1)
			return (fprintf(stderr, "Invalid Input\n"), 0);
		switch (choice)
		{
		case 1:
			out = ec_load("./beta");
			*key = out;
			printf("Default key set successfully\n");
			return (1);
		case 2:
			printf("Going back to CLI home\n");
			return (0);
		default:
			fprintf(stderr, "Invalid choice\n");
			return (0);
		}
	}

	out = ec_load(arg1);
	if (!out)
		return (fprintf(stderr, "Failed to load from folder %s\n", arg1), 0);
	*key = out;
	printf("Wallet loaded successfully\n");
	display_compressed(*key);
	return (1);
	(void)bc;
	(void)active;
	(void)arg2;
}
