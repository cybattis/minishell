
NAME		=	minishell

SRCS		=	utils.c env.c redirection.c terminal.c heredoc.c		\
				utils2.c env_utils.c

PARS_DIR	=	parsing
PARSING		=	parsing.c command_split.c minishell_error.c get_redirections.c get_redirections_helper.c				\
				parsing_helper.c get_next_word.c get_single_quotes.c get_double_quotes.c get_env_var_split.c			\
				get_env_var_raw.c env_var_helper.c parsing_error.c file_and_directories.c strip_out_operators.c			\
				tokenize.c lexer.c token_type.c command_batch.c cleanup.c get_next_word_splitted.c unfinished_quote.c	\
				ask_for_quote.c

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

DEPENDS		=	$(addprefix $(OBJS_DIR)/, $(OBJS:.o=.d))

# Recipe
# ****************************************************************************

.PHONY: all
all:	$(NAME)

$(OBJS_DIR)/%.o:	$(SRCS_DIR)/exec/%.c | $(OBJS_DIR)
	@$(BIN_CC) $(BIN_CFLAGS) -c $< -o $@
	@printf "$(_GREEN)█$(_END)"

$(OBJS_DIR)/%.o:	$(SRCS_DIR)/main/%.c | $(OBJS_DIR)
	@$(BIN_CC) $(BIN_CFLAGS) -c $< -o $@
	@printf "$(_GREEN)█$(_END)"

$(OBJS_DIR)/%.o:	$(SRCS_DIR)/parsing/%.c | $(OBJS_DIR)
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
	rm -f $(OBJS)

.PHONY: fclean
fclean: clean
	rm -f ../$(NAME)

re: fclean all

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

-include $(DEPENDS)
