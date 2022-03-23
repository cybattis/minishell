
NAME		=	minishell

SRCS		=	utils.c env.c redirection.c terminal.c heredoc.c		\
				utils2.c env_utils.c

PARS_DIR	=	parsing
PARSING		=	get_token.c lexer.c parsing.c command_batch.c			\
				parsing_error.c tokenizer.c command_batch_helper.c		\
				token_type.c env_handling.c

EXEC_DIR	=	exec
EXEC		=	execute.c exec_pipe.c builtins.c builtins_env.c

MAIN_DIR	=	main
MAIN		=	main.c get_line.c get_git_prompt.c get_prompt.c init.c	\
				signal.c

SRC_PARSING	=	$(addprefix $(PARS_DIR)/, $(PARSING))
SRC_EXEC	=	$(addprefix $(EXEC_DIR)/, $(EXEC))
SRC_MAIN	=	$(addprefix $(MAIN_DIR)/, $(MAIN))

OBJS		=	$(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))				\
				$(addprefix $(OBJS_DIR)/, $(PARSING:.c=.o))				\
				$(addprefix $(OBJS_DIR)/, $(EXEC:.c=.o))				\
				$(addprefix $(OBJS_DIR)/, $(MAIN:.c=.o))

HEADERS		=	$(MAKE_DIR)/includes/minishell.h

DEPENDS		=	$(addprefix $(OBJS_DIR)/, $(OBJS:.o=.d))

# Recipe
# ****************************************************************************

.PHONY: all
all:	$(NAME)

$(OBJS_DIR)/%.o:	$(SRCS_DIR)/*/%.c | $(OBJS_DIR)
	@$(BIN_CC) $(BIN_CFLAGS) -c $< -o $@
	@printf "$(_GREEN)█$(_END)"

$(OBJS_DIR)/%.o:	$(SRCS_DIR)/%.c | $(OBJS_DIR)
	@$(BIN_CC) $(BIN_CFLAGS) -c $< -o $@
	@printf "$(_GREEN)█$(_END)"

$(NAME):	$(OBJS) $(MASTER_MAKE) $(LIBFT_LIB)
	@printf "$(_BLUE)\nCompiled source files\n$(_END)"
	@$(BIN_CC) $(BIN_LDFLAGS) $(OBJS) -o ../$(NAME) $(LIBS)
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
