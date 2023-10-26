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
	/* construct the paths */
	char priv_path[256], pub_path[256];
	EC_KEY *key_pair, *pubkey;
	FILE *fpriv, *fpub;

	snprintf(priv_path, sizeof(priv_path), "%s%s", folder, "key.pem");
	snprintf(pub_path, sizeof(pub_path), "%s%s", folder, "key_pub.pem");

	if (!folder)
		return (NULL);

	fpriv = fopen(priv_path, "r");
	key_pair = PEM_read_ECPrivateKey(fpriv, NULL, NULL, NULL);
	fclose(fpriv);

	fpub = fopen(pub_path, "r");
	pubkey = PEM_read_EC_PUBKEY(fpub, NULL, NULL, NULL);
	fclose(fpub);

	/* set Public Key in EC_KEy struct => stderr specified NULL */
	/* provided to ec_to_pub() <= wasn't set ? */
	EC_KEY_set_public_key(key_pair, EC_KEY_get0_public_key(pubkey));

	EC_KEY_free(pubkey);
	return (key_pair);
}
