#include "hblk_crypto.h"

/**
 * ec_create - creates a new key pair
 * --> coordinates of point on the Elliptic Curve
 * Return: pointer to an EC_KEY structure, holding both
 * pub and priv keys, or NULL upon failure
 */

EC_KEY *ec_create(void)
{
	/* EC_KEY is treated as a 'blackbox' */
	EC_KEY *ekey = EC_KEY_new_by_curve_name(EC_CURVE);
	/* EC_KEY_new||new_by_curve_name||dup returns */
	/* pointer to the newly created EC_KEY||NULL error*/
	/* extra check to ensure it has an associated EC_GROUp*/
	if (!ekey || !(EC_KEY_get0_group(ekey)))
		return (NULL);
	if (!EC_KEY_generate_key(ekey))
		return (NULL);

	/* cleanup handled in test/main */

	return (ekey);
}
