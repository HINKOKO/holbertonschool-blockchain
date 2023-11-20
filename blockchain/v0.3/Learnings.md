# **Blockchain - Transactions**

## **General Learnings**

- **How to build a transaction**
- **What is a transaction input**
- **What is a transaction output**
- **Why to sign a transaction input**
- **How to compute the balance of given wallet**
- **What is a coinbase transaction and why it is used**
- **How to ensure immutability of a transaction**
- **What is the difference between the UTXO and the Account-based transaction models**

### **Folder structure**

By the end of the project, the folder structure will be updated to this state:

```
holbertonschool-blockchain
├── blockchain
│   ├── v0.1/
│   ├── v0.2/
│   └── v0.3
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
│       ├── libhblk_blockchain_v0.3.a
│       ├── Makefile
│       ├── provided
│       │   ├── _blockchain_print.c
│       │   ├── _endianness.c
│       │   ├── endianness.h
│       │   ├── _genesis.c
│       │   ├── _print_hex_buffer.c
│       │   └── _transaction_print.c
│       ├── test
│       │   ├── blockchain_create-main.c
│       │   ├── blockchain_deserialize-main.c
│       │   ├── blockchain_destroy-main.c
│       │   ├── blockchain_difficulty-main.c
│       │   ├── blockchain_serialize-main.c
│       │   ├── block_create-main.c
│       │   ├── block_destroy-main.c
│       │   ├── block_hash-main.c
│       │   ├── block_is_valid-main.c
│       │   ├── block_mine-main.c
│       │   └── hash_matches_difficulty-main.c
│       └── transaction
│           ├── coinbase_create.c
│           ├── coinbase_is_valid.c
│           ├── test
│           │   ├── coinbase_create-main.c
│           │   ├── coinbase_is_valid-main.c
│           │   ├── transaction_create-main.c
│           │   ├── transaction_destroy-main.c
│           │   ├── transaction_hash-main.c
│           │   ├── transaction_is_valid-main.c
│           │   ├── tx_in_create-main.c
│           │   ├── tx_in_sign-main.c
│           │   ├── tx_out_create-main.c
│           │   ├── unspent_tx_out_create-main.c
│           │   └── update_unspent-main.c
│           ├── transaction_create.c
│           ├── transaction_destroy.c
│           ├── transaction.h
│           ├── transaction_hash.c
│           ├── transaction_is_valid.c
│           ├── tx_in_create.c
│           ├── tx_in_sign.c
│           ├── tx_out_create.c
│           ├── unspent_tx_out_create.c
│           └── update_unspent.c
├── crypto/
└── README.md
```
