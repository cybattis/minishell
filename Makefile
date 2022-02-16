MAKE_DIR		:=		$(PWD)

MASTER_MAKE		:=		$(MAKE_DIR)/Makefile

SRCS_DIR		:=		$(MAKE_DIR)/src

LIB_DIR			:=		$(MAKE_DIR)/libft

INC_PATH		:=		-I$(LIB_DIR)

LIB_PATH		:=		-L$(LIB_DIR)

LIBS			:=		-lft

BIN_CC			:=		gcc

BIN_CFLAGS		:=
BIN_CFLAGS		+=		$(INC_PATH) $(LIB_PATH) $(LIBS)
BIN_CFLAGS		+=		-MD
BIN_CFLAGS		+=		-Wall -Werror -Wextra
BIN_CFLAGS		+=		-fsanitize=address

BIN_LDFLAGS		:=
BIN_LDFLAGS		+=		-fsanitize=address

LIBFT_LIB		:=		$(LIB_DIR)/libftd.a

export MAKE_DIR
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

.PHONY: re
re: fclean all
