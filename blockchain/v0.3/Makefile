compiler = gcc -Wall -Wextra -Werror -pedantic -g3 -I. -Itransaction/ -Iprovided/ -I../../crypto
flags = -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread

lib-files = \
blockchain_create.o \
block_create.o \
block_destroy.o \
blockchain_destroy.o \
block_hash.o \
blockchain_serialize.o \
blockchain_deserialize.o \
block_is_valid.o \
hash_matches_difficulty.o \
blockchain_difficulty.o \
block_mine.o \
tx_out_create.o \
unspent_tx_out_create.o \
tx_in_create.o \
transaction_hash.o \
tx_in_sign.o \
transaction_create.o \
transaction_is_valid.o \
coinbase_create.o \
coinbase_is_valid.o \
transaction_destroy.o \
update_unspent.o

libhblk_blockchain.a: $(lib-files)
	ar rcs libhblk_blockchain.a $(lib-files)

blockchain_create.o: blockchain_create.c
	$(compiler) -c blockchain_create.c $(flags)
block_create.o: block_create.c
	$(compiler) -c block_create.c $(flags)
block_destroy.o: block_destroy.c
	$(compiler) -c block_destroy.c $(flags)
blockchain_destroy.o: blockchain_destroy.c
	$(compiler) -c blockchain_destroy.c $(flags)
block_hash.o: block_hash.c
	$(compiler) -c block_hash.c $(flags)
blockchain_serialize.o: blockchain_serialize.c
	$(compiler) -c blockchain_serialize.c $(flags)
blockchain_deserialize.o: blockchain_deserialize.c
	$(compiler) -c blockchain_deserialize.c $(flags)
block_is_valid.o: block_is_valid.c
	$(compiler) -c block_is_valid.c $(flags)
hash_matches_difficulty.o: hash_matches_difficulty.c
	$(compiler) -c hash_matches_difficulty.c $(flags)
blockchain_difficulty.o: blockchain_difficulty.c
	$(compiler) -c blockchain_difficulty.c $(flags)
block_mine.o: block_mine.c
	$(compiler) -c block_mine.c $(flags)
tx_out_create.o: transaction/tx_out_create.c
	$(compiler) -c transaction/tx_out_create.c $(flags)
unspent_tx_out_create.o: transaction/unspent_tx_out_create.c
	$(compiler) -c transaction/unspent_tx_out_create.c $(flags)
tx_in_create.o: transaction/tx_in_create.c
	$(compiler) -c transaction/tx_in_create.c $(flags)
transaction_hash.o: transaction/transaction_hash.c
	$(compiler) -c transaction/transaction_hash.c $(flags)
tx_in_sign.o: transaction/tx_in_sign.c
	$(compiler) -c transaction/tx_in_sign.c $(flags)
transaction_create.o: transaction/transaction_create.c
	$(compiler) -c transaction/transaction_create.c $(flags)
transaction_is_valid.o: transaction/transaction_is_valid.c
	$(compiler) -c transaction/transaction_is_valid.c $(flags)
coinbase_create.o: transaction/coinbase_create.c
	$(compiler) -c transaction/coinbase_create.c $(flags)
coinbase_is_valid.o: transaction/coinbase_is_valid.c
	$(compiler) -c transaction/coinbase_is_valid.c $(flags)
transaction_destroy.o: transaction/transaction_destroy.c
	$(compiler) -c transaction/transaction_destroy.c $(flags)
update_unspent.o: transaction/update_unspent.c
	$(compiler) -c transaction/update_unspent.c $(flags)

files-0 = transaction/tx_out_create.c provided/_print_hex_buffer.c transaction/test/tx_out_create-main.c
task0: $(files-0)
	$(compiler) -o task0 $(files-0) $(flags)

files-1 = transaction/tx_out_create.c transaction/unspent_tx_out_create.c provided/_print_hex_buffer.c transaction/test/unspent_tx_out_create-main.c
task1: $(files-1)
	$(compiler) -o task1 $(files-1) $(flags)

files-2 = transaction/tx_out_create.c transaction/unspent_tx_out_create.c transaction/tx_in_create.c provided/_print_hex_buffer.c transaction/test/tx_in_create-main.c
task2: $(files-2)
	$(compiler) -o task2 $(files-2) $(flags)

files-3 = transaction/tx_out_create.c transaction/unspent_tx_out_create.c transaction/tx_in_create.c transaction/transaction_hash.c provided/_print_hex_buffer.c transaction/test/transaction_hash-main.c provided/_transaction_print.c
task3: $(files-3)
	$(compiler) -o task3 $(files-3) $(flags)

files-4 = transaction/tx_out_create.c transaction/unspent_tx_out_create.c transaction/tx_in_create.c transaction/transaction_hash.c transaction/tx_in_sign.c provided/_print_hex_buffer.c transaction/test/tx_in_sign-main.c provided/_transaction_print.c
task4: $(files-4)
	$(compiler) -o task4 $(files-4) $(flags)

files-5 = transaction/tx_out_create.c transaction/unspent_tx_out_create.c transaction/tx_in_create.c transaction/transaction_hash.c transaction/tx_in_sign.c transaction/transaction_create.c provided/_print_hex_buffer.c provided/_transaction_print.c transaction/test/transaction_create-main.c
task5: $(files-5)
	$(compiler) -o task5 $(files-5) $(flags)

files-6 = transaction/tx_out_create.c transaction/unspent_tx_out_create.c transaction/tx_in_create.c transaction/transaction_hash.c transaction/tx_in_sign.c transaction/transaction_is_valid.c provided/_print_hex_buffer.c transaction/test/transaction_is_valid-main.c provided/_transaction_print.c
task6: $(files-6)
	$(compiler) -o task6 $(files-6) $(flags)

files-7 = transaction/tx_out_create.c transaction/transaction_hash.c transaction/coinbase_create.c provided/_print_hex_buffer.c transaction/test/coinbase_create-main.c provided/_transaction_print.c
task7: $(files-7)
	$(compiler) -o task7 $(files-7) $(flags)

files-8 = transaction/tx_out_create.c transaction/transaction_hash.c transaction/coinbase_create.c transaction/coinbase_is_valid.c provided/_print_hex_buffer.c transaction/test/coinbase_is_valid-main.c provided/_transaction_print.c
task8: $(files-8)
	$(compiler) -o task8 $(files-8) $(flags)

files-9 = transaction/tx_out_create.c transaction/tx_in_create.c transaction/transaction_hash.c transaction/tx_in_sign.c transaction/transaction_create.c transaction/coinbase_create.c transaction/transaction_destroy.c transaction/test/transaction_destroy-main.c
task9: $(files-9)
	$(compiler) -o task9 $(files-9) $(flags)

files-11 = test/blockchain_destroy-main.c *.c transaction/*.c provided/*.c
task11: $(files-11)
	$(compiler) -o task11 $(files-11) $(flags)

files-12 = blockchain_create.c block_create.c block_destroy.c blockchain_destroy.c block_hash.c transaction/tx_out_create.c transaction/tx_in_create.c transaction/transaction_hash.c transaction/coinbase_create.c transaction/transaction_destroy.c provided/_genesis.c provided/_print_hex_buffer.c provided/_blockchain_print.c provided/_transaction_print.c provided/_transaction_print_brief.c test/block_hash-main.c
task12: $(files-12)
	$(compiler) -o task12 $(files-12) $(flags)

files-13 = blockchain_create.c block_create.c block_destroy.c blockchain_destroy.c block_hash.c block_is_valid.c hash_matches_difficulty.c blockchain_difficulty.c block_mine.c transaction/tx_out_create.c transaction/unspent_tx_out_create.c transaction/tx_in_create.c transaction/transaction_hash.c transaction/tx_in_sign.c transaction/transaction_create.c transaction/transaction_is_valid.c transaction/coinbase_create.c transaction/coinbase_is_valid.c transaction/transaction_destroy.c provided/_genesis.c provided/_print_hex_buffer.c test/block_is_valid-main.c
task13: $(files-13)
	$(compiler) -o task13 $(files-13) $(flags)

files-14 = blockchain_create.c block_create.c block_destroy.c blockchain_destroy.c block_hash.c block_is_valid.c hash_matches_difficulty.c blockchain_difficulty.c block_mine.c transaction/tx_out_create.c transaction/unspent_tx_out_create.c transaction/tx_in_create.c transaction/transaction_hash.c transaction/tx_in_sign.c transaction/transaction_create.c transaction/transaction_is_valid.c transaction/coinbase_create.c transaction/coinbase_is_valid.c transaction/transaction_destroy.c transaction/update_unspent.c provided/_genesis.c provided/_print_hex_buffer.c provided/_blockchain_print.c provided/_transaction_print.c provided/_transaction_print_brief.c transaction/test/update_unspent-main.c
task14: $(files-14)
	$(compiler) -o task14 $(files-14) $(flags)

files-15w = test/blockchain_serialize-main.c *.c transaction/*.c provided/*.c
task15-write: $(files-15w)
	$(compiler) -o task15-write $(files-15w) $(flags)
files-15r = test/blockchain_deserialize-main.c *.c transaction/*.c provided/*.c
task15-read: $(files-15r)
	$(compiler) -o task15-read $(files-15r) $(flags)
clean:
	rm task* $(lib-files) libhblk_blockchain.a
