# **Blockchain - Data structures**

At the end of this project **v0.1** the structure of repository should look like:

```
holbertonschool-blockchain
├── blockchain
│   ├── v0.1/
│   └── v0.2
│       ├── blockchain_create.c
│       ├── blockchain_deserialize.c
│       ├── blockchain_destroy.c
│       ├── blockchain_difficulty.c
│       ├── blockchain.h
│       ├── blockchain_serialize.c
│       ├── block_create.c
│       ├── block_destroy.c
│       ├── block_hash.c
│       ├── block_is_valid.c
│       ├── block_mine.c
│       ├── hash_matches_difficulty.c
│       ├── libhblk_blockchain_v0.2.a
│       ├── Makefile
│       ├── provided
│       │   ├── _blockchain_destroy.c
│       │   ├── _blockchain_print.c
│       │   ├── _endianness.c
│       │   ├── endianness.h
│       │   └── _genesis.c
│       └── test
│           ├── blockchain_create-main.c
│           ├── blockchain_deserialize-main.c
│           ├── blockchain_destroy-main.c
│           ├── blockchain_difficulty-main.c
│           ├── blockchain_serialize-main.c
│           ├── block_create-main.c
│           ├── block_destroy-main.c
│           ├── block_hash-main.c
│           ├── block_is_valid-main.c
│           ├── block_mine-main.c
│           └── hash_matches_difficulty-main.c
├── crypto/
└── README.md
```

## **Learning Objectives**

- **What is the purpose of the Block difficulty**

  The primary purpose of the block difficulty is to regulate the rate at which new blocks are added to the blockchain. The difficulty is dynamically adjusted at regular intervals (usually every few blocks) based on the network's overall hash rate. the block difficulty is kind of "scaling" with the network power involved in the process of mining a new block.

- **What is the Proof of Work**
  **Proof of Work** is achieved by **Mining** a block, and "Mining" refers to the process of solving a (difficult) computational puzzle, by trying out a maximum of solutions (as fast as can is best, according to the computer power you dispose of). <br>
  The **Proof-of-Work** adds security to the Blockchain but also balance => That Proof-of-Work kind of 'flexible', meaning it can regulate how often a Block should be added to the chain. This can be done by modifying the difficulty of the puzzle: If Blocks are solved and added too often, the difficulty (difficulty of **P**roving the **W**ork) increases, if Blocks candidates gets too rare, the difficulty decreases...<br>
  The difficulty is scaling with the Network involved power. Great.<br>

- **How to check that a given hash matches a given difficulty**
- **How to mine a Block**
- **Why Block mining is brute force only**
- **How to automatically adjust the difficulty**
