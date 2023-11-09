#include "blockchain.h"
#include "./provided/endianness.h"

uint8_t _get_endianness(void);

#define HBLK_MAGIC "HBLK"
#define HBLK_VERSION "0.1"

/**
 * record_block_content - Iterates over the chain
 * and for each block record its content in serialized file
 * @fd: file descriptor of file to write to
 * @blockchain: pointer to blockchain struct
 * Return: Nothing
 */

void record_block_content(int fd, blockchain_t const *blockchain)
{
	int idx;
	block_t *block = NULL;
	int size_of_chain = llist_size(blockchain->chain);

	for (idx = 0; idx < size_of_chain; idx++)
	{
		block = llist_get_node_at(blockchain->chain, idx);
		write(fd, &(block->info), sizeof(block->info));
		write(fd, &block->data.len, sizeof(block->data.len));
		write(fd, block->data.buffer, block->data.len);
		write(fd, block->hash, SHA256_DIGEST_LENGTH);
	}
}

/**
 * blockchain_serialize - serializes a Blockchain into a file
 * @blockchain: Points to the blockchain to serialize
 * @path: Contains the path to a file to serialize Blockchain into
 * must be overwritten if pointing to an existing file
 * Return: 0 on Success, -1 upon Failure
 *
 * 'write' instead of 'fwrite' at first
 * fwrite => Performs buffered I/O, means it may not write data immediately.
 * write => Performs unbuffered I/O, means it writes data directly to the file.
 */

int blockchain_serialize(blockchain_t const *blockchain,
						 char const *path)
{
	int fd, number_of_blocks = 0;
	uint8_t endian = _get_endianness();

	if (!blockchain || !path)
		return (-1); /* hassle user */

	fd = open(path, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (!fd)
		return (-1);

	number_of_blocks = llist_size(blockchain->chain);
	write(fd, HBLK_MAGIC, strlen(HBLK_MAGIC));
	write(fd, HBLK_VERSION, strlen(HBLK_VERSION));
	write(fd, &endian, sizeof(endian));
	write(fd, &number_of_blocks, sizeof(number_of_blocks));

	record_block_content(fd, blockchain);
	close(fd);
	return (0);
}
