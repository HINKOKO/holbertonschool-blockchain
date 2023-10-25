#include <stdio.h>
#include <stdlib.h>

#include "hblk_crypto.h"

void print_hex_buffer(uint8_t const *buf, size_t len);

/**
 * main - Entry point
 * @ac: argument count
 * @av: argument vector
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */

int main(int ac, char **av)
{
	EC_KEY *key;
	uint8_t pub[EC_PUB_LEN];

	if (ac < 2)
		return (fprintf(stderr, "Usage: %s <path>\n", av[0]), EXIT_FAILURE);

	key = ec_create();
	/* ec_create() creates a key/pair */
	/* pointer to EC_KEY struct holding both */
	ec_to_pub(key, pub);
	/* ec_to_pub() extracts the pub from EC_KEY */
	printf("Public key: ");
	print_hex_buffer(pub, EC_PUB_LEN);
	printf("\n");

	/* Test ec_save() */
	ec_save(key, av[1]);
	/* cleanup */
	EC_KEY_free(key);

	return (EXIT_SUCCESS);
}
