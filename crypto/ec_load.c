#include "hblk_crypto.h"

/* For pem encoding functions */
#include <openssl/pem.h>

/**
 * ec_load - loads an EC key pair from the disk
 * @folder: path to the folder from which to load
 * the EC key pair.
 * Return: SUCCESS -> A pointer to the created EC Key pair
 * FAILURE -> NULL
 */

EC_KEY *ec_load(char const *folder)
{
	char path[256] = {0};
	EC_KEY *key_pair = NULL;
	FILE *fkey;

	if (!folder)
		return (NULL);
	/* concatene path */
	sprintf(path, "%s/" PRI_FILENAME, folder);
	fkey = fopen(path, "r");
	if (!PEM_read_ECPrivateKey(fkey, &key_pair, NULL, NULL))
	{
		fclose(fkey);
		return (NULL);
	}
	fclose(fkey);

	/* concatene again, buffer will be flushed */
	sprintf(path, "%s/" PUB_FILENAME, folder);
	fkey = fopen(path, "r");
	if (!PEM_read_EC_PUBKEY(fkey, &key_pair, NULL, NULL))
	{
		EC_KEY_free(key_pair);
		fclose(fkey);
		return (NULL);
	}
	fclose(fkey);
	return (key_pair);
}
