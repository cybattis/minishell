
NAME		=	minishell

SRCS		=	main.c get_line.c signal.c execute.c utils.c builtins.c	\
				builtins_env.c get_prompt.c env.c init.c exec_pipe.c	\
				redirection.c terminal.c get_git_prompt.c heredoc.c		\
				utils2.c env_utils.c

PARS_DIR	=	parsing
PARSING		=	get_token.c lexer.c parsing.c command_batch.c			\
				parsing_error.c tokenizer.c command_batch_helper.c		\
				token_type.c env_handling.c

SRC_PARSING	=	$(addprefix $(PARS_DIR)/, $(PARSING))


OBJS		=	$(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
OBJS_PARS	=	$(addprefix $(OBJS_DIR)/, $(PARSING:.c=.o))

HEADERS		=	$(MAKE_DIR)/includes/minishell.h

DEPENDS		=	$(addprefix $(OBJS_DIR)/, $(SRCS:.c=.d))				\
				$(addprefix $(OBJS_DIR)/, $(OBJS_PARS:.c=.d))

# Recipe
# ****************************************************************************

.PHONY: all
all:	$(NAME)

$(OBJS_DIR)/%.o:	$(SRCS_DIR)/$(PARS_DIR)/%.c | $(OBJS_DIR)
	@$(BIN_CC) $(BIN_CFLAGS) -c $< -o $@
	@printf "$(_GREEN)█$(_END)"

$(OBJS_DIR)/%.o:	$(SRCS_DIR)/%.c | $(OBJS_DIR)
	@$(BIN_CC) $(BIN_CFLAGS) -c $< -o $@
	@printf "$(_GREEN)█$(_END)"

$(NAME):	$(OBJS) $(OBJS_PARS) $(MASTER_MAKE) $(LIBFT_LIB)
	@printf "$(_BLUE)\nCompiled source files\n$(_END)"
	@$(BIN_CC) $(BIN_LDFLAGS) $(OBJS) $(OBJS_PARS) -o ../$@ $(LIBS)
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
