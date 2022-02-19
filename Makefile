MAKE_DIR		:=		$(PWD)

MASTER_MAKE		:=		$(MAKE_DIR)/Makefile

SRCS_DIR		:=		$(MAKE_DIR)/src
OBJS_DIR		:=		$(MAKE_DIR)/obj

LIB_DIR			:=		$(MAKE_DIR)/libft

INC_PATH		:=		-I$(LIB_DIR) -I$(MAKE_DIR)/includes

LIB_PATH		:=		-L$(LIB_DIR)

LIBS			:=		-lftd

OS				=	$(shell uname -s)
ifeq ($(OS), Linux)
	READLINE		:=		-L/usr/lib/x86_64-linux-gnu/ -lreadline -lhistory
	INC_PATH		+=
else
	READLINE		:=		-L ~/.brew/Cellar/readline/8.1.2/lib -lreadline
	INC_PATH		+=		-I ~/.brew/Cellar/readline/8.1.2/include/readline
endif

BIN_CC			:=		gcc

BIN_CFLAGS		:=
BIN_CFLAGS		+=		-MD
BIN_CFLAGS		+=		-Wall -Wextra
BIN_CFLAGS		+=		-g3 -fsanitize=address
BIN_CFLAGS		+=		$(INC_PATH)

BIN_LDFLAGS		:=
BIN_LDFLAGS		+=		$(LIB_PATH) $(LIBS)
BIN_LDFLAGS		+=		-fsanitize=address

LIBFT_LIB		:=		$(LIB_DIR)/libftd.a

export MAKE_DIR
export OBJS_DIR
export MASTER_MAKE
export SRCS_DIR
export OBJS_DIR
export INC_PATH
export LIB_PATH
export LIBS
export BIN_CC
export BIN_CFLAGS
export BIN_LDFLAGS
export LIBFT_LIB
export LIB_PATH
export READLINE

.PHONY: all
all: header
	@$(MAKE) -C $(LIB_DIR)
	@$(MAKE) -C $(SRCS_DIR)/parsing -r -R --warn-undefined-variables
	@$(MAKE) -C $(SRCS_DIR) -r -R --warn-undefined-variables

debug: header
	@$(MAKE) -C $(LIB_DIR) debug
	@$(MAKE) -C $(SRCS_DIR)/parsing -r -R --warn-undefined-variables
	@$(MAKE) -C $(SRCS_DIR) -r -R --warn-undefined-variables

.PHONY: bonus
bonus: all

.PHONY: clean
clean: header
	@$(MAKE) -C $(LIB_DIR) clean
	@$(MAKE) -C $(SRCS_DIR) clean

.PHONY: fclean
fclean:
	@$(MAKE) -C $(LIB_DIR) fclean
	@$(MAKE) -C $(SRCS_DIR) fclean

.PHONY: tests
tests:
	@$(MAKE) -C $(LIB_DIR) debug
	@$(MAKE) -C src/parsing/ tests

.PHONY: re
re: fclean all debug clean bonus

.PHONY: header
header:
	@printf "\n"
	@printf "$(_YELLOW)\t░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░$(_END)\n"
	@printf "$(_YELLOW)\t░   ░░░░░░░   ░   ░    ░░░░░   ░   ░░░      ░░░   ░░░░   ░         ░   ░░░░░░░   ░░░░░░░$(_END)\n"
	@printf "$(_YELLOW)\t▒  ▒   ▒▒▒    ▒   ▒  ▒   ▒▒▒   ▒   ▒   ▒▒▒▒   ▒   ▒▒▒▒   ▒   ▒▒▒▒▒▒▒   ▒▒▒▒▒▒▒   ▒▒▒▒▒▒▒$(_END)\n"
	@printf "$(_YELLOW)\t▒   ▒   ▒ ▒   ▒   ▒   ▒   ▒▒   ▒   ▒▒   ▒▒▒▒▒▒▒   ▒▒▒▒   ▒   ▒▒▒▒▒▒▒   ▒▒▒▒▒▒▒   ▒▒▒▒▒▒▒$(_END)\n"
	@printf "$(_YELLOW)\t▓   ▓▓   ▓▓   ▓   ▓   ▓▓   ▓   ▓   ▓▓▓▓   ▓▓▓▓▓          ▓       ▓▓▓   ▓▓▓▓▓▓▓   ▓▓▓▓▓▓▓$(_END)\n"
	@printf "$(_YELLOW)\t▓   ▓▓▓  ▓▓   ▓   ▓   ▓▓▓  ▓   ▓   ▓▓▓▓▓▓▓   ▓▓   ▓▓▓▓   ▓   ▓▓▓▓▓▓▓   ▓▓▓▓▓▓▓   ▓▓▓▓▓▓▓$(_END)\n"
	@printf "$(_YELLOW)\t▓   ▓▓▓▓▓▓▓   ▓   ▓   ▓▓▓▓  ▓  ▓   ▓   ▓▓▓▓   ▓   ▓▓▓▓   ▓   ▓▓▓▓▓▓▓   ▓▓▓▓▓▓▓   ▓▓▓▓▓▓▓$(_END)\n"
	@printf "$(_YELLOW)\t█   ███████   █   █   ██████   █   ███      ███   ████   █         █         █         █$(_END)\n"
	@printf "$(_YELLOW)\t████████████████████████████████████████████████████████████████████████████████████████$(_END)\n"
	@printf "\n"

# Colors
# ****************************************************************************

_GREY	= \033[30m
_RED	= \033[31m
_GREEN	= \033[32m
_YELLOW	= \033[33m
_BLUE	= \033[34m
_PURPLE	= \033[35m
_CYAN	= \033[36m
_WHITE	= \033[37m
_END	= \033[0m

export _GREY
export _GREEN
export _YELLOW
export _BLUE
export _PURPLE
export _CYAN
export _WHITE
export _END


# ****************************************************************************
