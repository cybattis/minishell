
NAME		=	minishell

SRCS		=	main.c io.c signal.c execute.c utils.c
OBJS		=	$(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

SRC_PARSING	=	get_token.c lexer.c parsing.c var_expansion.c command_batch.c	\
				parsing_error.c
OBJ_PARSING	=	$(addprefix $(OBJS_DIR)/, $(SRC_PARSING:.c=.o))

HEADERS		=	$(MAKE_DIR)/includes/minishell.h

DEPENDS		=	$(addprefix $(OBJS_DIR)/, $(SRCS:.c=.d))

# Recipe
# ****************************************************************************

.PHONY: all
all:	$(NAME)

$(OBJS_DIR)/%.o:	$(SRCS_DIR)/%.c | $(OBJS_DIR)
	@$(BIN_CC) $(BIN_CFLAGS) -c $< -o $@
	@printf "$(_GREEN)█$(_END)"

$(NAME):	$(OBJS) $(MASTER_MAKE) $(LIBFT_LIB)
	@printf "$(_BLUE)\nCompiled source files\n"
	@$(BIN_CC) $(BIN_CFLAGS) $(OBJS) $(OBJ_PARSING) $(LIBFT_LIB) $(READLINE) -o ../$@
	@printf "$(_GREEN)Finish compiling $(NAME)!$(_END)\n"

.PHONY: bonus
bonus: all

.PHONY: clean
clean:
	rm -rf $(OBJS_DIR)

.PHONY: fclean
fclean: clean
	rm -f ../$(NAME)

re: fclean all

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

-include $(DEPENDS)
