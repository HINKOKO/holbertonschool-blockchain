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
	EC_KEY *eckey = EC_KEY_new();
	FILE *fpriv = NULL, *fpub = NULL;

	if (!folder || !eckey)
		return (NULL);

	fpriv = fopen(folder, "r");
	eckey = PEM_read_ECPrivateKey(fpriv, &eckey, NULL, NULL);
	fclose(fpriv);

	fpub = fopen(folder, "r");
	eckey = PEM_read_EC_PUBKEY(fpub, &eckey, NULL, NULL);
	fclose(fpub);

	EC_KEY_free(eckey);
	return (eckey);
}
