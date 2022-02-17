MAKE_DIR		:=		$(PWD)

MASTER_MAKE		:=		$(MAKE_DIR)/Makefile

SRCS_DIR		:=		$(MAKE_DIR)/src/
OBJS_DIR		:=		$(MAKE_DIR)/objs/

LIB_DIR			:=		$(MAKE_DIR)/libft

INC_PATH		:=		-I$(LIB_DIR)

LIB_PATH		:=		-L$(LIB_DIR)

LIBS			:=		-lftd

BIN_CC			:=		gcc

BIN_CFLAGS		:=
BIN_CFLAGS		+=		$(INC_PATH)
BIN_CFLAGS		+=		-MD
BIN_CFLAGS		+=		-Wall -Werror -Wextra
BIN_CFLAGS		+=		-fsanitize=address

BIN_LDFLAGS		:=
BIN_LDFLAGS		+=		$(LIB_PATH) $(LIBS)
BIN_LDFLAGS		+=		-fsanitize=address

LIBFT_LIB		:=		$(LIB_DIR)/libftd.a

export MAKE_DIR
export OBJS_DIR
export MASTER_MAKE
export INC_PATH
export LIB_PATH
export LIBS
export BIN_CC
export BIN_CFLAGS
export BIN_LDFLAGS
export LIBFT_LIB

.PHONY: all
all:
	@$(MAKE) -C $(LIB_DIR) debug

.PHONY: bonus
bonus: all

.PHONY: clean
clean:
	@$(MAKE) -C $(LIB_DIR) clean

.PHONY: fclean
fclean:
	@$(MAKE) -C $(LIB_DIR) fclean

.PHONY: tests
tests:
	@$(MAKE) -C $(LIB_DIR) debug
	@$(MAKE) -C src/parsing/ tests

.PHONY: re
re: fclean all
