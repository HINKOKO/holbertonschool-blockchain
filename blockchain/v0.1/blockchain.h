#ifndef __BCHAIN_STRUCT__
#define __BCHAIN_STRUCT__

#define BLOCKCHAIN_DATA_MAX 1024

#include "../../crypto/hblk_crypto.h"
/* Linked list lib */
#include <llist.h>

#include <stdio.h>
#include <stdlib.h>
/* To maintain same sizes on != architectures */
#include <stdint.h>

/**
 * struct blockchain_s - Blockchain structure
 * @chain: Linked linst of pointers to block_t
 */
typedef struct blockchain_s
{
	llist_t *chain;
} blockchain_t;

/**
 * struct block_info_s - Block info structure
 * @index: Index of the Block in the Blockchain
 * @difficulty: Difficulty of proof of work (hash leading zero bits)
 * @timestamp: Time the Block was created (Unix time)
 * @nonce: Salt value used to alter the Block hash
 * @prev_hash: Hash of the previous Block in the Blockchain
 *
 * Note => order of element in this struct matters a lot:
 * it was designed so every element is ALIGNED and do not require
 * PADDING from the compiler => CPU is happy.
 * Also, it is therefore possible to use the struct as an array of chars
 * on any architecture.
 */
typedef struct block_info_s
{
	uint32_t index;
	uint32_t difficulty;
	uint64_t timestamp;
	uint64_t nonce;
	uint8_t prev_hash[SHA256_DIGEST_LENGTH];
} block_info_t;

/**
 * struct block_data_s - Block data structure
 * @buffer: Data buffer
 * Buffer hold up to 1024 element,each being signed 8-bit int
 * @len: Data size (bytes)
 * buffer must stay first (array of chars usage
 * to remain possible)
 */
typedef struct block_data_s
{
	int8_t buffer[BLOCKCHAIN_DATA_MAX];
	uint32_t len;
} block_data_t;

/**
 * struct block_s - Block structure
 * @info: Block info
 * @data: Block data
 * @hash: 256-bit digest of the Block, to ensure authenticity
 */
typedef struct block_s
{
	block_info_t info;
	block_data_t data;
	uint8_t hash[SHA256_DIGEST_LENGTH];
} block_t;

/* Prototypes */
blockchain_t *blockchain_create(void);
block_t *block_create(block_t const *prev, int8_t const *data, uint32_t data_len);
void block_destroy(block_t *block);
void blockchain_destroy(blockchain_t *blockchain);
uint8_t *block_hash(block_t const *block, uint8_t hash_buf[SHA256_DIGEST_LENGTH]);
int blockchain_serialize(blockchain_t const *blockchain, char const *path);
blockchain_t *blockchain_deserialize(char const *path);
int block_is_valid(block_t const *block, block_t const *prev_block);

#endif /* __BCHAIN_STRUCT__ */