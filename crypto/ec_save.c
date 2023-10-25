#include "hblk_crypto.h"

/* For pem encoding functions */
#include <openssl/pem.h>

#include <sys/stat.h>
#include <sys/types.h>

/**
 * ec_save - saves an existing Key pair on the disk
 * @key: Points to the EC key pair to be saved
 * @folder: Path to the folder in which to save keys
 * Return: 1 || 0 success/failure respectively
 * => 'folder' must be created if it doesn't exists already
 */

int ec_save(EC_KEY *key, char const *folder)
{
	char path[256] = {0};
	FILE *fp;

	if (!key || !folder)
		return (0);

	mkdir(folder, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	/* USe the macro for private key filename */
	sprintf(path, "%s/" PRI_FILENAME, folder);
	fp = fopen(path, "w+");
	/* Privacy-Enhanced Mail encode the private key */
	PEM_write_ECPrivateKey(fp, key, NULL, NULL, 0, NULL, NULL);
	/* close the private key file.pem */
	fclose(fp);

	/* sprintf overrides previous call to sprintf => path cleared */
	sprintf(path, "%s/" PUB_FILENAME, folder);
	fp = fopen(path, "w+");
	PEM_write_EC_PUBKEY(fp, key);

	fclose(fp);
	return (1);
}
