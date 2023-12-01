CC               = gcc
LINK_DIR         = ../../crypto
DIR              = transaction
LINKS            = $(addprefix -l, ssl hblk_crypto crypto llist) -pthread
INCLUDE          = $(addprefix -I, . $(DIR)/ $(LINK_DIR)/ provided/)
CFLAGS           = -g3 -Wall -Werror -Wextra -pedantic $(INCLUDE)
PRINTER          = provided/_print_hex_buffer.c
BLOCKCHAIN_FILES = blockchain_create.c block_create.c block_destroy.c blockchain_destroy.c block_hash.c blockchain_serialize.c blockchain_deserialize.c block_is_valid.c hash_matches_difficulty.c blockchain_difficulty.c block_mine.c

T0 = tx_out_create
$(T0)_files       = $(addprefix $(DIR)/, $(T0).c test/$(T0)-main.c) $(PRINTER)
$(T0): $($(T0)_files:.c=.o)
	$(CC) $(CFLAGS) $($(T0)_files) -o $(DIR)/$(T0)-test -L$(LINK_DIR) $(LINKS)

T1 = unspent_tx_out_create
$(T1)_files       = $(addprefix $(DIR)/, $(T0).c $(T1).c test/$(T1)-main.c) $(PRINTER)
$(T1): $($(T1)_files:.c=.o)
	$(CC) $(CFLAGS) $($(T1)_files) -o $(DIR)/$(T1)-test -L$(LINK_DIR) $(LINKS)

T2 = tx_in_create
$(T2)_files       = $(addprefix $(DIR)/, $(T0).c $(T1).c $(T2).c test/$(T2)-main.c) $(PRINTER)
$(T2): $($(T2)_files:.c=.o)
	$(CC) $(CFLAGS) $($(T2)_files) -o $(DIR)/$(T2)-test -L$(LINK_DIR) $(LINKS)

T3 = transaction_hash
$(T3)_files       = $(addprefix $(DIR)/, $(T0).c $(T1).c $(T2).c $(T3).c test/$(T3)-main.c) $(PRINTER) provided/_transaction_print.c
$(T3): $($(T3)_files:.c=.o)
	$(CC) $(CFLAGS) $($(T3)_files) -o $(DIR)/$(T3)-test -L$(LINK_DIR) $(LINKS)

T4 = tx_in_sign
$(T4)_files       = $(addprefix $(DIR)/, $(T0).c $(T1).c $(T2).c $(T3).c $(T4).c test/$(T4)-main.c) $(PRINTER) provided/_transaction_print.c
$(T4): $($(T4)_files:.c=.o)
	$(CC) $(CFLAGS) $($(T4)_files) -o $(DIR)/$(T4)-test -L$(LINK_DIR) $(LINKS)

T5 = transaction_create
$(T5)_files       = $(addprefix $(DIR)/, $(T0).c $(T1).c $(T2).c $(T3).c $(T4).c $(T5).c test/$(T5)-main.c) $(PRINTER) provided/_transaction_print.c
$(T5): $($(T5)_files:.c=.o)
	$(CC) $(CFLAGS) $($(T5)_files) -o $(DIR)/$(T5)-test -L$(LINK_DIR) $(LINKS)

T6 = transaction_is_valid
$(T6)_files       = $(addprefix $(DIR)/, $(T0).c $(T1).c $(T2).c $(T3).c $(T4).c $(T5).c $(T6).c test/$(T6)-main.c) $(PRINTER) provided/_transaction_print.c
$(T6): $($(T6)_files:.c=.o)
	$(CC) $(CFLAGS) $($(T6)_files) -o $(DIR)/$(T6)-test -L$(LINK_DIR) $(LINKS)

T7 = coinbase_create
$(T7)_files       = $(addprefix $(DIR)/, $(T0).c $(T3).c $(T7).c test/$(T7)-main.c) $(PRINTER) provided/_transaction_print.c
$(T7): $($(T7)_files:.c=.o)
	$(CC) $(CFLAGS) $($(T7)_files) -o $(DIR)/$(T7)-test -L$(LINK_DIR) $(LINKS)

T8 = coinbase_is_valid
$(T8)_files       = $(addprefix $(DIR)/, $(T0).c $(T3).c $(T7).c $(T8).c test/$(T8)-main.c) $(PRINTER) provided/_transaction_print.c
$(T8): $($(T8)_files:.c=.o)
	$(CC) $(CFLAGS) $($(T8)_files) -o $(DIR)/$(T8)-test -L$(LINK_DIR) $(LINKS)


T9 = transaction_destroy
$(T9)_files       = $(addprefix $(DIR)/, $(T0).c $(T2).c $(T3).c $(T4).c $(T5).c $(T7).c $(T9).c test/$(T9)-main.c) $(PRINTER) provided/_transaction_print.c
$(T9): $($(T9)_files:.c=.o)
	$(CC) $(CFLAGS) $($(T9)_files) -o $(DIR)/$(T9)-test -L$(LINK_DIR) $(LINKS)


T10 = update_unspent
$(T10)_files       = $(addprefix $(DIR)/, $(T0).c $(T1).c $(T2).c $(T3).c $(T4).c $(T5).c $(T6).c $(T7).c $(T8).c $(T9).c $(T10).c test/$(T10)-main.c) $(PRINTER) provided/_transaction_print.c provided/_genesis.c provided/_blockchain_print.c provided/_transaction_print_brief.c $(BLOCKCHAIN_FILES)
$(T10): $($(T10)_files:.c=.o)
	$(CC) $(CFLAGS) $($(T10)_files) -o $(DIR)/$(T10)-test -L$(LINK_DIR) $(LINKS)

T11 = blockchain_serialize
$(T11)_files       = $(addprefix $(DIR)/, $(T0).c $(T1).c $(T2).c $(T3).c $(T4).c $(T5).c $(T6).c $(T7).c $(T8).c $(T9).c $(T10).c) test/$(T11)-main.c $(PRINTER) provided/_transaction_print.c provided/_genesis.c provided/_blockchain_print.c provided/_transaction_print_brief.c $(BLOCKCHAIN_FILES)
$(T11): $($(T11)_files:.c=.o)
	$(CC) $(CFLAGS) $($(T11)_files) -o $(T11)-test -L$(LINK_DIR) $(LINKS)

T12 = blockchain_deserialize
$(T12)_files       = $(addprefix $(DIR)/, $(T0).c $(T1).c $(T2).c $(T3).c $(T4).c $(T5).c $(T6).c $(T7).c $(T8).c $(T9).c $(T10).c) test/$(T12)-main.c $(PRINTER) provided/_transaction_print.c provided/_genesis.c provided/_blockchain_print.c provided/_transaction_print_brief.c $(BLOCKCHAIN_FILES)
$(T12): $($(T12)_files:.c=.o)
	$(CC) $(CFLAGS) $($(T12)_files) -o $(T12)-test -L$(LINK_DIR) $(LINKS)

FILES = $(addprefix $(DIR)/, $(T0) $(T1) $(T2) $(T3) $(T4) $(T5) $(T6) $(T7) $(T8) $(T9) $(T10))
OBJ_FILES = $(BLOCKCHAIN_FILES:.c=.o) $(addsuffix .o,$(FILES)) 
libhblk_blockchain.a: $(OBJ_FILES)
	ar rcs libhblk_blockchain.a $(OBJ_FILES)
