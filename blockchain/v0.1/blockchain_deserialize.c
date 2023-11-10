#include "blockchain.h"

#define BUFSIZE 2048
#define CLEAR_BUFF memset(buf, 0, BUFSIZE)
#define CLEAR_N_LOAD(x) ((memset(buf, 0, BUFSIZE)), (read(fd, buf, x)))

uint8_t _get_endianness(void);

/**
 * load_blocks - After checking the header
 * `load_blocks` iterate through the Blockchain to
 * read and deserialize the blocks from data file save.hblk
 * @fd: opened file descriptor
 * @blocks: number of blocks
 *
 * Return: Pointer to linked list of blocks
 * bchain->chain
 *
 */

llist_t *load_blocks(int fd, uint32_t blocks)
{
	llist_t *bchain = llist_create(MT_SUPPORT_TRUE);
	block_t *block = NULL; /* here we gonna create blocks */
	uint32_t idx;

	for (idx = 0; idx < blocks; idx++)
	{
		block = calloc(1, sizeof(*block));
		if (!block)
			return (NULL);
		if (read(fd, &(block->info), sizeof(block_info_t)) < 0 ||
			read(fd, &(block->data.len), sizeof(int)) < 0 ||
			read(fd, block->data.buffer, block->data.len) < 0 ||
			read(fd, block->hash, SHA256_DIGEST_LENGTH) < 0)
			return (free(block), NULL);

		if (llist_add_node(bchain, block, ADD_NODE_REAR) < 0)
			return (free(block), NULL);
	}
	return (bchain);
}

/**
 * blockchain_deserialize - Deserializes (load) Bchain
 * from a file provided in 'path'
 * @path: path to the file to load the serialized Bchain from
 *
 * Return: Pointer to deserialized Bchain on Success, NULL Failure
 */

blockchain_t *blockchain_deserialize(char const *path)
{
	int fd;
	blockchain_t *Bchain = NULL;
	char buf[BUFSIZE] = {0};
	uint8_t endian;
	uint32_t blocks = 0;

	if (!path)
		return (NULL);
	fd = open(path, O_RDONLY);
	if (!fd)
		return (NULL); /* read permission not set */
	/* Let's go */
	CLEAR_N_LOAD(strlen(HBLK_MAGIC));
	if (strcmp(buf, HBLK_MAGIC))
		return (NULL);

	CLEAR_N_LOAD(strlen(HBLK_VERSION));
	if (strcmp(buf, HBLK_VERSION))
		return (NULL);

	CLEAR_N_LOAD(1);
	endian = *buf;
	if (endian != _get_endianness())
		return (NULL);

	CLEAR_N_LOAD(4);
	blocks = *buf;

	Bchain = calloc(1, sizeof(*Bchain));
	if (!Bchain)
		return (NULL);
	Bchain->chain = load_blocks(fd, blocks);
	close(fd);
	return (Bchain);
}
